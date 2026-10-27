"""Sample discovery, selection, and lossless additions for practice workspaces."""
import json
from pathlib import Path
import re


def sample_files(workspace):
    inputs = sorted((p for p in workspace.glob('*.in')
                     if p.is_file() and re.fullmatch(r'[1-9][0-9]*', p.stem)),
                    key=lambda p: int(p.stem))
    if inputs:
        return [(p, workspace / (p.stem + '.expected.txt'),
                 workspace / (p.stem + '.output.txt')) for p in inputs]
    return [(workspace / 'input.txt', workspace / 'expected.txt', workspace / 'output.txt')]


def selected_samples(workspace, selection=''):
    samples = sample_files(workspace)
    if not selection:
        return samples
    if not re.fullmatch(r'[1-9][0-9]*', selection):
        raise ValueError('SAMPLE must be a positive integer, such as SAMPLE=2.')
    selected = [s for s in samples if (s[0].stem if s[0].suffix == '.in' else '1') == selection]
    if not selected or not selected[0][0].is_file():
        raise ValueError('Sample ' + selection + ' does not exist; use make samples problem.cpp.')
    return selected


def add_sample(workspace, input_file, expected_file):
    """Append a pair, copying a legacy sample to 1 without changing its original files."""
    if not input_file or not expected_file:
        raise ValueError('Use INPUT=path/to/input EXPECTED=path/to/answer with sample-add.')
    incoming = (Path(input_file).expanduser().read_bytes(), Path(expected_file).expanduser().read_bytes())
    numbered = [p for p in workspace.iterdir()
                if re.fullmatch(r'[1-9][0-9]*\.(?:in|expected\.txt|output\.txt)', p.name)]
    writes = {}
    if numbered:
        # Reserve orphan expected/output names too: never overwrite a partial sample.
        index = max(int(p.name.split('.')[0]) for p in numbered) + 1
        if not any(p.suffix == '.in' for p in numbered):
            raise ValueError('Numbered sample artifacts exist without inputs; resolve them first.')
    else:
        input_path, expected_path, output_path = sample_files(workspace)[0]
        old_input, old_expected = input_path.read_bytes(), expected_path.read_bytes()
        metadata = workspace / 'problem.json'
        has_imported_sample = metadata.is_file() and bool(json.loads(metadata.read_text()).get('tests'))
        index = 1
        if old_input or old_expected or has_imported_sample:
            writes.update({'1.in': old_input, '1.expected.txt': old_expected,
                           '1.output.txt': output_path.read_bytes() if output_path.is_file() else b''})
            index = 2
    writes.update({f'{index}.in': incoming[0], f'{index}.expected.txt': incoming[1],
                   f'{index}.output.txt': b''})
    created = []
    try:
        for name, data in writes.items():
            path = workspace / name
            with path.open('xb') as stream:
                created.append(path)
                stream.write(data)
    except BaseException:
        for path in reversed(created):
            path.unlink()
        raise
    return index
