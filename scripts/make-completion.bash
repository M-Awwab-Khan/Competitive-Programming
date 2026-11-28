# Tab completion for problem filenames: make run|check|build|debug|samples|sample-add <TAB>
# Source from ~/.bashrc:  source ~/workspace/competitive-programming/scripts/make-completion.bash
# Candidates come from scripts/complete_names.py. Typing a prefix completes it as
# usual; when nothing starts with what you typed, names containing those letters in
# order (case-insensitive, e.g. "rctsum" -> Rectangle_Sum.cpp) are listed best first.

_CP_COMPLETE_NAMES="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)/complete_names.py"

_cp_make() {
    local cur=${COMP_WORDS[COMP_CWORD]} action= i
    if [[ -f scripts/problem.py && $cur != -* && $cur != *=* ]]; then
        for ((i = 1; i < COMP_CWORD; i++)); do
            case ${COMP_WORDS[i]} in
                build|run|check|debug|samples|sample-add) action=${COMP_WORDS[i]} ;;
            esac
        done
        if [[ -n $action ]]; then
            local out mode
            out=$(python3 "$_CP_COMPLETE_NAMES" "$PWD" "$cur" 2>/dev/null) || return
            mode=${out%%$'\n'*}
            if [[ $out == *$'\n'* ]]; then
                mapfile -t COMPREPLY <<<"${out#*$'\n'}"
            else
                COMPREPLY=()
            fi
            # Keep the ranking for fuzzy matches instead of readline's alphabetical sort.
            [[ $mode == fuzzy ]] && compopt -o nosort 2>/dev/null
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
