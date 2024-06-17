#!/usr/bin/env bash

TESTS=(
    assert
    atof
    atoi
    ctype
    exit
    main
    printf
    string
)

function main() {
    for test in "${TESTS[@]}"; do
        printf "%-10s .. " "$test"

        if [[ ! -x "c/${test}" ]]; then
            printf "No such file\n"
            continue
        fi

        if diff -q <("c/${test}" 2>/dev/null) <(wasm/wasm-run.py "wasm/${test}.wasm" 2>/dev/null) >/dev/null; then
            printf "Pass\n"
        else
            printf "Error\n"
        fi
    done
}

main "$@"
