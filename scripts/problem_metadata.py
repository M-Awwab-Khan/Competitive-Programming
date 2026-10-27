"""Read optional Competitive Companion identity without inferring classifications or verdicts."""
import json
import re
from urllib.parse import unquote, urlsplit


def problem_title(name):
    return re.sub(r'^\s*[A-Za-z][0-9]*\.\s+', '', name).strip()


def companion_metadata(source, root):
    relative = source.relative_to(root)
    path = source.parent / 'problem.json'
    if relative.parts[:2] != ('practice', 'inbox') or len(relative.parts) != 4 or not path.is_file():
        return {}
    try:
        payload = json.loads(path.read_text())
        if not isinstance(payload, dict):
            raise ValueError('Expected a JSON object')
        title, url = payload.get('name'), payload.get('url')
        if not isinstance(title, str) or not title.strip() or not isinstance(url, str):
            raise ValueError('Expected nonempty name and URL strings')
        parsed = urlsplit(url)
        if parsed.scheme not in ('http', 'https') or not parsed.hostname:
            raise ValueError('Expected an HTTP(S) URL')
        result = dict(title=problem_title(title) or title, urls=[url], collections=[])
        group = payload.get('group')
        if isinstance(group, str) and group.strip():
            result['collections'] = [group]
        host = parsed.hostname.lower()
        if host == 'codeforces.com' or host.endswith('.codeforces.com'):
            result['platform'] = 'codeforces'
            match = re.search(r'/(?:problemset/problem|contest|gym)/(\d+)/(?:problem/)?([A-Za-z][0-9]*)/?$', parsed.path)
            if match:
                result['problem_id'] = match[1] + match[2]
        elif host == 'vjudge.net' or host.endswith('.vjudge.net'):
            result['platform'] = 'vjudge'
            match = re.fullmatch(r'/problem/([^/]+)/?', parsed.path)
            contest = re.fullmatch(r'/contest/(\d+)/?', parsed.path)
            letter = re.fullmatch(r'problem/([A-Za-z0-9]+)', parsed.fragment)
            if match:
                result['problem_id'] = unquote(match[1])
            elif contest and letter:
                result['problem_id'] = 'contest-' + contest[1] + '-' + letter[1]
        for field, key in [('timeLimit', 'time_limit_ms'), ('memoryLimit', 'memory_limit_mb')]:
            value = payload.get(field)
            if value is not None:
                if type(value) is not int or value <= 0:
                    raise ValueError(field + ' must be a positive integer')
                result[key] = value
        if 'interactive' in payload:
            if not isinstance(payload['interactive'], bool):
                raise ValueError('interactive must be a boolean')
            result['interactive'] = payload['interactive']
        return result
    except (ValueError, OSError) as exc:
        raise ValueError(f'Invalid Companion metadata in {path}: {exc}') from exc
