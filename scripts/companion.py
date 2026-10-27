#!/usr/bin/env python3
"""Receive Competitive Companion problems locally and choose a language in the terminal."""
import argparse
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import queue
import re
import shutil
import sys
import threading
import unicodedata
from urllib.parse import urlsplit

from problem import LANGUAGES, ROOT
from problem_metadata import problem_title

PORT = 10043  # A default Competitive Companion custom-tool port.
MAX_BYTES = 4 * 1024 * 1024
CHROME_ORIGIN = 'chrome-extension://cjnmckjndlpiamhfimnnjmnckgghkjbl'


def validate(payload):
    if not isinstance(payload, dict):
        raise ValueError('Expected a problem JSON object.')
    for field in ('name', 'url'):
        if not isinstance(payload.get(field), str) or not payload[field].strip():
            raise ValueError('Missing or invalid ' + field)
    url = urlsplit(payload['url'])
    if url.scheme not in ('http', 'https') or not url.hostname:
        raise ValueError('Expected an HTTP(S) problem URL.')
    tests = payload.get('tests')
    if not isinstance(tests, list):
        raise ValueError('Expected a tests array.')
    for test in tests:
        if not isinstance(test, dict) or any(not isinstance(test.get(k), str)
                                             for k in ('input', 'output')):
            raise ValueError('Each sample needs string input and output.')
    return payload


def problem_name(payload):
    """Use the readable title; keep platform identity in problem.json."""
    title = problem_title(payload['name'])
    title = unicodedata.normalize('NFKD', title).encode('ascii', 'ignore').decode()
    name = re.sub(r'[^A-Za-z0-9_-]+', '_', title).strip('_-')[:100].rstrip('_-')
    return name or 'problem'


def import_problem(payload, lang, root=ROOT):
    """Create a separate attempt on collision; preserve payload and sample bytes."""
    validate(payload)
    if lang not in ('cpp', 'py'):
        raise ValueError('Choose cpp or py.')
    content = (root / 'templates' / ('cpp/problem.cpp' if lang == 'cpp'
                                   else 'python/problem.py')).read_bytes()
    base = problem_name(payload)
    parent = root / 'practice/inbox'
    parent.mkdir(parents=True, exist_ok=True)
    attempt = 1
    while True:
        name = base if attempt == 1 else base + '-attempt-' + str(attempt)
        workspace = parent / name
        try:
            workspace.mkdir()
            break
        except FileExistsError:
            attempt += 1
    try:
        source = workspace / (name + '.' + lang)
        source.write_bytes(content)
        (workspace / 'problem.json').write_text(json.dumps(payload, ensure_ascii=False, indent=2) + '\n')
        tests = payload['tests']
        if len(tests) <= 1:
            test = tests[0] if tests else {'input': '', 'output': ''}
            samples = [('input.txt', 'expected.txt', 'output.txt', test)]
        else:
            samples = [(f'{i}.in', f'{i}.expected.txt', f'{i}.output.txt', test)
                       for i, test in enumerate(tests, 1)]
        for input_name, expected_name, output_name, test in samples:
            (workspace / input_name).write_bytes(test['input'].encode('utf-8'))
            (workspace / expected_name).write_bytes(test['output'].encode('utf-8'))
            (workspace / output_name).write_bytes(b'')
    except BaseException:
        shutil.rmtree(workspace)
        raise
    return source


def make_server(pending, port):
    class Handler(BaseHTTPRequestHandler):
        def log_message(self, *_):
            pass

        def reply(self, status, message):
            body = json.dumps({'message': message}).encode()
            self.send_response(status)
            if self.headers.get('Origin') == CHROME_ORIGIN:
                self.send_header('Access-Control-Allow-Origin', CHROME_ORIGIN)
            self.send_header('Content-Type', 'application/json')
            self.send_header('Content-Length', str(len(body)))
            self.end_headers()
            self.wfile.write(body)

        def allowed(self):
            # Reject ordinary web-page requests and DNS rebinding hosts.
            return (self.headers.get('Origin') in (None, CHROME_ORIGIN)
                    and self.headers.get('Host') in (
                        f'localhost:{self.server.server_port}',
                        f'127.0.0.1:{self.server.server_port}'))

        def do_OPTIONS(self):
            if not self.allowed():
                self.reply(403, 'Only Competitive Companion is allowed.')
                return
            self.send_response(204)
            self.send_header('Access-Control-Allow-Origin', CHROME_ORIGIN)
            self.send_header('Access-Control-Allow-Methods', 'POST, OPTIONS')
            self.send_header('Access-Control-Allow-Headers', 'Content-Type')
            self.end_headers()

        def do_POST(self):
            self.connection.settimeout(5)
            if not self.allowed():
                self.reply(403, 'Only Competitive Companion is allowed.')
                return
            if self.path != '/':
                self.reply(404, 'POST to /')
                return
            try:
                length = int(self.headers.get('Content-Length', '0'))
                if not 0 < length <= MAX_BYTES:
                    self.reply(413, 'Payload must be between 1 byte and 4 MiB.')
                    return
                payload = validate(json.loads(self.rfile.read(length)))
                pending.put_nowait(payload)
            except queue.Full:
                self.reply(503, 'Import queue full; finish pending imports first.')
                return
            except (ValueError, UnicodeError, OSError) as exc:
                self.reply(400, str(exc))
                return
            self.reply(200, 'Queued; choose the language in your terminal.')

    return ThreadingHTTPServer(('127.0.0.1', port), Handler)


def choose_language(payload, read=input):
    print('\nImport: ' + payload['name'] + '\n' + payload['url'], flush=True)
    while True:
        answer = read('Language [cpp/py], or s to skip: ').strip().lower()
        if answer == 's':
            return None
        if answer in LANGUAGES:
            return LANGUAGES[answer]
        print('Enter cpp or py (or s to skip).')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=PORT,
                        help='Default 10043; add other ports in Companion custom ports.')
    args = parser.parse_args()
    if not sys.stdin.isatty():
        parser.error('Run in an interactive terminal so you can choose a language.')
    if not 1 <= args.port <= 65535:
        parser.error('Port must be between 1 and 65535.')
    pending = queue.Queue(maxsize=100)
    try:
        server = make_server(pending, args.port)
    except OSError as exc:
        parser.error(f'Cannot listen on port {args.port}: {exc}. Stop the other listener '
                     'or use --port and set Companion custom ports.')
    thread = threading.Thread(target=server.serve_forever, daemon=True)
    thread.start()
    print(f'Listening for Competitive Companion on 127.0.0.1:{args.port}.\n'
          'Click its icon on a problem page, then choose cpp or py here. Ctrl-C stops.', flush=True)
    try:
        while True:
            try:
                payload = pending.get(timeout=0.5)
            except queue.Empty:
                continue
            lang = choose_language(payload)
            if lang is None:
                print('Skipped.')
                continue
            try:
                source = import_problem(payload, lang)
            except (ValueError, OSError) as exc:
                print('Import failed: ' + str(exc), file=sys.stderr)
                continue
            print('Created ' + str(source.relative_to(ROOT)))
            print(f'In another terminal: make run {source.name}\n'
                  f'                     make check {source.name}', flush=True)
            if not payload['tests']:
                print('No published samples received; fill input.txt and expected.txt.')
            if payload.get('interactive'):
                print('Interactive problem: use an interactive runner; sample checks are insufficient.')
    except (KeyboardInterrupt, EOFError):
        print('\nReceiver stopped; any queued imports were not created.')
    finally:
        server.shutdown()
        server.server_close()
        thread.join()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
