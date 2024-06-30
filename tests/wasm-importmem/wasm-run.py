#!/bin/bash

##############################################################################
# BOOTSTRAP
#
# Include ../lib in the search path then call python3 or python.
# (Thanks to https://unix.stackexchange.com/questions/20880)
#
if "true" : '''\'
then
    export PYTHONPATH="$(dirname $0)/../lib:$PYTHONPATH"
    pythoncmd=python

    if command -v python3 >/dev/null; then
        pythoncmd=python3
    fi

    exec "$pythoncmd" "$0" "$@"
    exit 127
fi
'''

##############################################################################
# PYTHON CODE BEGINS HERE

import os
import sys
import errno
import getopts
from wasmer import engine, Store, Module, Instance, ImportObject, Function, Memory, MemoryType
from wasmer_compiler_llvm import Compiler

__copyright__ = "Copyright 2024 Mark Kim"
__license__ = "Apache 2.0"
__author__ = "Mark Kim"


##############################################################################
# GLOBALS

SCRIPTNAME = os.path.basename(__file__)

class opts:
    files = []


##############################################################################
# USAGE

def usage():
    """\
A program to run a wasm binary.  This version imports its own memory to the
wasm binary.

Usage: {SCRIPTNAME} [OPTIONS] [FILES]

Options:
  FILE                  WASM file(s) to execute.
"""

    print(usage.__doc__.format(**globals()))


##############################################################################
# MAIN

def main():
    errcount = 0

    # Process options
    getopt = getopts.getopts(sys.argv, {
        "h" : 0, "help" : 0,
    })

    for c in getopt:
        if   c in ("-")         : opts.files.append(getopt.optarg)
        elif c in ("h", "help") : usage(); sys.exit(0)
        else                    : errcount += 1

    # Sanity check
    if errcount:
        sys.stderr.write("Type `{SCRIPTNAME} --help` for help.\n".format(**globals()))
        sys.exit(1)

    for file in opts.files:
        doMyThing(file)


def doMyThing(file):
    store = Store()
    memory = Memory(store, MemoryType(minimum=2))
    memory8 = memory.uint8_view()

    def read(fd:"i32", buf:"i32", count:"i32") -> "i32":
        data = os.read(fd, count)
        count = len(data);
        memory8[buf:buf+count] = data;

        return count

    def write(fd:"i32", buf:"i32", count:"i32") -> "i32":
        return os.write(fd, bytearray(memory8[buf:buf+count]))

    def _exit(status:"i32") -> None:
        sys.exit(status)

    with open(file, mode="rb") as fd:
        wasm = fd.read()
        module = Module(store, wasm)
        instance = Instance(module, {
            "env": {
                "memory" : memory,
                "read"   : Function(store, read),
                "write"  : Function(store, write),
                "_exit"  : Function(store, _exit),
            }
        })

        result = instance.exports._start()


##############################################################################
# ENTRY POINT

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("")
        sys.exit(errno.EOWNERDEAD)


# vim:ft=python
