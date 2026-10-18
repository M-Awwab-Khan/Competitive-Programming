"""C++ compilation with an optional GCC PCH, isolated from archived sources."""
import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def compiler_config():
    compiler = shlex.split(os.environ.get('CXX') or 'g++')
    flags = shlex.split(os.environ.get('CPPFLAGS', ''))
    flags += shlex.split(os.environ.get('CXXFLAGS') or '-std=c++23 -O2 -pipe')
    version = subprocess.check_output(compiler + ['--version'], text=True)
    executable = shutil.which(compiler[0])
    identity = [compiler, flags, version, executable]
    if executable:
        stat = Path(executable).stat()
        identity.append([stat.st_size, stat.st_mtime_ns])
    return compiler, flags, identity


def fingerprint(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()[:20]


def fresh(state, signature, output):
    try:
        saved = json.loads(state.read_text())
        return output.is_file() and saved['signature'] == signature and all(
            [Path(name).stat().st_mtime_ns, Path(name).stat().st_size] == stats
            for name, stats in saved['dependencies'].items())
    except (OSError, ValueError, KeyError, TypeError):
        return False


def compile_cached(command, output, signature):
    state = output.with_name(output.name + '.json')
    if fresh(state, signature, output):
        return output
    output.parent.mkdir(parents=True, exist_ok=True)
    depfile = output.with_name(output.name + '.d')
    # Remove the old state before compilation: a failed build cannot be reused.
    state.unlink(missing_ok=True)
    print('Compiling ' + str(output.relative_to(ROOT)), flush=True)
    subprocess.run(command + ['-MD', '-MF', str(depfile), '-MT', 'artifact',
                              '-o', str(output)], cwd=ROOT, check=True)
    dependencies = {}
    # GCC escapes spaces/backslashes in Make dependency files.
    entries = depfile.read_text().replace('\\\n', '').split(':', 1)[1]
    for name in shlex.split(entries):
        path = Path(name.replace('$$', '$'))
        if not path.is_absolute():
            path = ROOT / path
        stat = path.stat()
        dependencies[str(path)] = [stat.st_mtime_ns, stat.st_size]
    state.write_text(json.dumps({'signature': signature, 'dependencies': dependencies}))
    return output


def prepare_pch(config=None):
    compiler, flags, identity = config or compiler_config()
    # Clang uses a different PCH mechanism. It can still compile the sources normally.
    macros = subprocess.check_output(compiler + flags + ['-dM', '-E', '-x', 'c++', '-'],
                                     input='', text=True)
    if '#define __GNUC__ ' not in macros or '#define __clang__ ' in macros:
        raise ValueError('PCH requires GCC/g++; use PCH=0 with another compiler.')
    header = ROOT / 'bits/stdc++.h'
    key = fingerprint([identity, str(ROOT), hashlib.sha256(header.read_bytes()).hexdigest()])
    directory = ROOT / 'build/pch' / key
    copied = directory / 'bits/stdc++.h'
    copied.parent.mkdir(parents=True, exist_ok=True)
    if not copied.exists() or copied.read_bytes() != header.read_bytes():
        copied.write_bytes(header.read_bytes())
    includes = ['-I', str(directory), '-I', str(ROOT)]
    output = copied.with_name(copied.name + '.gch')
    compile_cached(compiler + flags + includes + ['-x', 'c++-header', str(copied)],
                   output, fingerprint([identity, includes, key]))
    return directory


def build(source, use_pch=False):
    source = Path(source).resolve()
    compiler, flags, identity = compiler_config()
    includes = []
    pch_stamp = None
    if use_pch:
        directory = prepare_pch((compiler, flags, identity))
        includes += ['-I', str(directory)]
        stat = (directory / 'bits/stdc++.h.gch').stat()
        pch_stamp = [stat.st_mtime_ns, stat.st_size]
    includes += ['-I', str(ROOT)]
    # Warn if a source defines incompatible macros before including the PCH.
    command = compiler + flags + includes + ['-Winvalid-pch', str(source)]
    suffix = '.exe' if os.name == 'nt' else ''
    output = ROOT / 'build/problems' / (source.stem + '-' + fingerprint(str(source)) + suffix)
    return compile_cached(command, output, fingerprint([identity, includes, str(source), pch_stamp]))
