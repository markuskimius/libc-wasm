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
A program to run a wasm binary.

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


class WasmIface:
    def __init__(self, instance):
        self.instance = instance
        self.memory8 = instance.exports.memory.uint8_view()
        self.addrByString = dict()

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        for addr in self.addrByString.values():
            self.instance.exports.free(addr)

    def strdup(self, string):
        if string not in self.addrByString:
            addr = self.instance.exports.malloc(len(string)+1)
            self.memory8[addr:addr+len(string)] = string.encode("utf-8")
            self.memory8[addr+len(string)] = 0

            self.addrByString[string] = addr

        return self.addrByString[string]

    def strat(self, addr):
        len = 0

        while(self.memory8[addr+len] != 0):
            len += 1

        return bytearray(self.memory8[addr:addr+len]).decode("utf-8")


def doMyThing(file):
    store = Store()
    memory8 = None

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
                "read"   : Function(store, read),
                "write"  : Function(store, write),
                "_exit"  : Function(store, _exit),
            }
        })

        memory8 = instance.exports.memory.uint8_view()

        with WasmIface(instance) as wasm:
            instance.exports.shout(wasm.strdup("Hello"), wasm.strdup("world"))


##############################################################################
# ENTRY POINT

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("")
        sys.exit(errno.EOWNERDEAD)


# vim:ft=python
