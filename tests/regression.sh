#!/usr/bin/env bash

TESTS=(
    alloc
    asprintf
    assert
    atof
    atoi
    ctype
    exit
    isprint
    main
    math
    pow
    printf
    string
)

function main() {
    for test in "${TESTS[@]}"; do
        local outfile="regression.out/${test}.diff"
        local skipfile="regression.out/${test}.skip"

        printf "%-10s .. " "$test"

        if [[ ! -x "c/${test}" ]]; then
            printf "No such file\n"
            continue
        fi

        if diff -u <("c/${test}" 2>/dev/null) <(wasm/wasm-run.py "wasm/${test}.wasm" 2>/dev/null) > "$outfile"; then
            printf "Pass\n"
            rm -f "$outfile"
        elif [[ -r "$skipfile" ]]; then
            if grep -vFf "$skipfile" <(tail -n +3 "$outfile") | grep '^[-+]' >&/dev/null; then
                printf "Error\n"
            else
                printf "Ok\n"
            fi
        else
            printf "Error\n"
        fi
    done
}

main "$@"
