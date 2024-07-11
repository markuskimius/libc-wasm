# libc-wasm
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![Release](https://img.shields.io/github/v/release/markuskimius/libc-wasm?include_prereleases&label=Pre-release)](https://github.com/markuskimius/libc-wasm/releases)
![clang17](https://img.shields.io/badge/clang-17-blue.svg)
![wasm](https://img.shields.io/badge/wasm-32-blue.svg)

A small subset of the C library to build a vanilla WASM program.


## Installation

Requires clang17 or later, wasm-ld, and llvm-ar.
They all come with the llvm package.

```bash
$ make
$ sudo mkdir -p /opt/wasm
$ sudo make PREFIX=/opt/wasm install
```


## Building with libc-wasm

To build a binary with libc-wasm:

```bash
$ clang -I/opt/wasm/include --target=wasm32 -c myprogram.c
$ wasm-ld -L/opt/wasm/lib myprogram.o -lc-wasm -o myprogram.wasm
```


## Running the wasm program

The host language is expected to provide the following functions:

* read
* write
* _exit

Call the exported _start() function to run the wasm program.

Note: _start() does not return.  Instead, the program ends by calling the
_exit() function provided by the host language.  The host language is expected
to terminate the wasm process once _exit() is called.


## Supported Types

* FILE
* int16\_t
* int32\_t
* int64\_t
* int8\_t
* intmax\_t
* size\_t
* ssize\_t
* uint16\_t
* uint32\_t
* uint64\_t
* uint8\_t
* uintmax\_t


## Supported Globals

* NULL
* M\_PI
* errno
* stdin
* stdout
* stderr
* CHAR\_MAX
* CHAR\_MIN
* INT\_MAX
* INT\_MIN
* LLONG\_MAX
* LLONG\_MIN
* LONG\_MAX
* LONG\_MIN
* SHRT\_MAX
* SHRT\_MIN
* UCHAR\_MAX
* UINT\_MAX
* ULLONG\_MAX
* ULONG\_MAX
* USHRT\_MAX

... plus various error constants.


## Supported Functions/Macros

* assert
* atof
* atoi
* ceil
* clearerr
* fabs
* feof
* ferror
* fflush
* fgetc
* fileno
* floor
* fprintf
* fputc
* fread
* free
* fwrite
* getc
* isatty
* isdigit
* isinf
* isnan
* isspace
* isxdigit
* malloc
* memcpy
* memset
* pow
* printf
* putc
* realloc
* round
* sbrk
* snprintf
* sqrt
* strcasecmp
* strchr
* strcmp
* strdup
* strlen
* strncasecmp
* strncat
* strncmp
* strncpy
* strrchr
* strtod
* strtol
* strtoll
* tolower
* toupper
* vfprintf
* vprintf
* vsnprintf


## Supported Printf Formatters

Flags:

* `#`
* `0`
* `-`
* ` `
* `+`

Field widths:

* `l`
* `ll`
* `z`

Conversion specifiers:

* `c`
* `s`
* `f`
* `d`, `i`
* `o`, `u`, `x`, `X`
* `p`


## License

[Apache 2.0](LICENSE)
