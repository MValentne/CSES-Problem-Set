# shellcheck shell=bash
# _lib.sh - Shared helpers for the CSES helper scripts (build / test / run).
# This file is sourced, never executed directly.

# --- Colors -----------------------------------------------------------------
if [ -t 1 ]; then
    C_RED=$'\e[31m'
    C_GREEN=$'\e[32m'
    C_YELLOW=$'\e[33m'
    C_CYAN=$'\e[36m'
    C_DIM=$'\e[2m'
    C_BOLD=$'\e[1m'
    C_RESET=$'\e[0m'
else
    C_RED="" C_GREEN="" C_YELLOW="" C_CYAN="" C_DIM="" C_BOLD="" C_RESET=""
fi

_die() {
    printf '%serror:%s %s\n' "$C_RED" "$C_RESET" "$1" >&2
    exit 1
}

# --- Source detection -------------------------------------------------------
_detect_source() {
    if [ -f "main.cpp" ]; then
        SRC_FILE="main.cpp"
        COMPILER="${CXX:-g++}"
        LANG_STD="c++17"
    elif [ -f "main.c" ]; then
        SRC_FILE="main.c"
        COMPILER="${CC:-gcc}"
        LANG_STD="c11"
    else
        _die "No main.cpp or main.c found in $(pwd). Run this from a problem directory."
    fi
}

_build_flags() { # $1 = build mode: release | debug | sanitize
    local mode="${1:-release}"
    case "$mode" in
        release)  MODE_FLAGS=(-O2 -g) ;;
        debug)    MODE_FLAGS=(-O0 -g) ;;
        sanitize) MODE_FLAGS=(-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer) ;;
        *) _die "Unknown build mode '$mode' (expected release, debug or sanitize)" ;;
    esac
    BUILD_FLAGS=(-std="$LANG_STD" -Wall -Wextra "${MODE_FLAGS[@]}")
    # Optional user extras, e.g. CSES_CXXFLAGS="-DLOCAL"
    if [ -n "${CSES_CXXFLAGS:-}" ]; then
        # Intentional word splitting of user-provided flags
        read -r -a EXTRA_FLAGS <<< "$CSES_CXXFLAGS"
        BUILD_FLAGS+=("${EXTRA_FLAGS[@]}")
    else
        EXTRA_FLAGS=()
    fi
}

_compile() { # $1 = mode -> builds .build/main and writes .build/stamp
    local mode="${1:-release}"
    _detect_source
    _build_flags "$mode"
    local flags_str="${BUILD_FLAGS[*]}"
    mkdir -p .build

    printf '%s» compiling %s [%s]%s\n' "$C_YELLOW" "$SRC_FILE" "$mode" "$C_RESET"
    printf '%s  %s %s%s\n' "$C_DIM" "$COMPILER" "$flags_str" "$C_RESET"
    if ! "$COMPILER" "${BUILD_FLAGS[@]}" "$SRC_FILE" -o ".build/main"; then
        printf '%sCompilation failed.%s\n' "$C_RED" "$C_RESET" >&2
        return 1
    fi
    printf '%s|%s|%s\n' "$SRC_FILE" "$COMPILER" "$flags_str" > .build/stamp
    printf '%s✓ Build OK -> .build/main%s\n' "$C_GREEN" "$C_RESET"
}

# Ensures .build/main exists and is up to date.
# Optional $1 = force a specific build mode (recompiles if the stamp differs).
_ensure_binary() {
    _detect_source
    local want_mode="${1:-}"
    local stamp=""
    [ -f ".build/stamp" ] && stamp="$(<.build/stamp)"

    local need=0
    [ ! -f ".build/main" ] && need=1
    [ "$SRC_FILE" -nt ".build/main" ] && need=1
    if [ -n "$want_mode" ] && [ $need -eq 0 ]; then
        _build_flags "$want_mode"
        [ "$stamp" != "$SRC_FILE|$COMPILER|${BUILD_FLAGS[*]}" ] && need=1
    fi

    if [ $need -eq 1 ]; then
        _compile "${want_mode:-release}" || exit 1
    else
        printf '%s• using cached .build/main (up to date)%s\n' "$C_DIM" "$C_RESET"
    fi
}

# --- Timing -----------------------------------------------------------------
_now_ms() {
    local t
    if [ -n "${EPOCHREALTIME:-}" ]; then
        t="$EPOCHREALTIME"
        echo $(( ${t%.*} * 1000 + 10#${t#*.} / 1000 ))
    else
        t="$(date +%s%N)"
        echo $(( ${t%${t#?????????}} / 1000000 ))
    fi
}

_fmt_ms() {
    if [ "$1" -ge 10000 ]; then
        printf '%d.%ds' $(( $1 / 1000 )) $(( ($1 % 1000) / 100 ))
    else
        printf '%dms' "$1"
    fi
}

# --- Test discovery ---------------------------------------------------------
# Sets TESTS_DIR to "tests", "." or "" depending on where *.in files live.
_find_tests_dir() {
    TESTS_DIR=""
    if [ -d "tests" ]; then
        TESTS_DIR="tests"
    elif compgen -G "*.in" > /dev/null; then
        TESTS_DIR="."
    fi
}

_list_in_files() { # prints newline-separated list, version-sorted
    [ -n "$TESTS_DIR" ] || return 0
    local -a files=()
    local f
    for f in "$TESTS_DIR"/*.in; do
        [ -f "$f" ] && files+=("$f")
    done
    [ ${#files[@]} -eq 0 ] && return 0
    printf '%s\n' "${files[@]}" | sort -V
}
