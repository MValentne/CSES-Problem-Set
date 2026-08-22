# shellcheck shell=bash
# _test_wrapper.sh - Sourced by `activate` and .envrc.
#
# `test` is a shell *builtin*, so a script named `test` on the PATH would never
# run when typed directly. This function shadows the builtin ONLY when called
# the way our runner is used (test, test 3, test 1-5, test --list ...).
# Any classic usage such as `test -f file` still hits the real builtin.

if [ -z "${CSES_SCRIPTS_DIR:-}" ]; then
    CSES_SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]:-$0}" )" && pwd )"
    export CSES_SCRIPTS_DIR
fi

test() {
    local a
    for a in "$@"; do
        case "$a" in
            [0-9]*|[0-9]*-[0-9]*|-*) ;;                       # looks like ours
            *) builtin test "$@"; return ;;                   # classic usage
        esac
    done
    "$CSES_SCRIPTS_DIR/test" "$@"
}
