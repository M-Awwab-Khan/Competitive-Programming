# Tab completion for problem filenames: make run|check|build|debug|samples|sample-add <TAB>
# Source from ~/.bashrc:  source ~/workspace/competitive-programming/scripts/make-completion.bash
# Candidates are the NAME.cpp / NAME.py files `make` can resolve: sources still in
# practice/inbox/NAME/ and filed sources whose catalog original_path is there.

_cp_problem_names() {
    python3 - "$1" <<'PY'
import json, sys
from pathlib import Path
root = Path(sys.argv[1])
names = set()
inbox = root / 'practice/inbox'
if inbox.is_dir():
    for d in inbox.iterdir():
        if d.is_dir():
            names.update(f.name for f in d.glob(d.name + '.*') if f.suffix in ('.cpp', '.py'))
try:
    for p in json.loads((root / 'catalog/problems.json').read_text(encoding='utf-8'))['problems']:
        parts = Path(p['original_path']).parts
        if len(parts) == 4 and parts[:2] == ('practice', 'inbox') and parts[3].rsplit('.', 1)[-1] in ('cpp', 'py'):
            names.add(parts[3])
except (OSError, ValueError, KeyError):
    pass
print('\n'.join(sorted(names)))
PY
}

_cp_make() {
    local cur=${COMP_WORDS[COMP_CWORD]} action= i
    if [[ -f scripts/problem.py && $cur != -* && $cur != *=* ]]; then
        for ((i = 1; i < COMP_CWORD; i++)); do
            case ${COMP_WORDS[i]} in
                build|run|check|debug|samples|sample-add) action=${COMP_WORDS[i]} ;;
            esac
        done
        if [[ -n $action ]]; then
            local IFS=$'\n'
            COMPREPLY=($(compgen -W "$(_cp_problem_names "$PWD")" -- "$cur"))
            return
        fi
    fi
    # Fall back to the stock make completion (renamed _comp_cmd_make in newer bash-completion).
    local fn
    for fn in _comp_cmd_make _make; do
        declare -F "$fn" >/dev/null && { "$fn" "$@"; return; }
    done
    _completion_loader make 2>/dev/null
    for fn in _comp_cmd_make _make; do
        declare -F "$fn" >/dev/null && { "$fn" "$@"; return; }
    done
}
complete -F _cp_make make
