# libc-wasm
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)
[![Release](https://img.shields.io/github/v/release/markuskimius/libc-wasm?include_prereleases&label=Pre-release)](https://github.com/markuskimius/libc-wasm/releases)
![clang17](https://img.shields.io/badge/clang-17-blue.svg)
![wasm](https://img.shields.io/badge/wasm-blue.svg)

A small subset of the C library to build a vanilla WASM program.


## Installation

Requires clang17 or later, wasm-ld, and wasm-ar.

```bash
$ sudo mkdir -p /opt/wasm
$ sudo make PREFIX=/opt/wasm install
```


## Building with libc-wasm

To build a binary with libc-wasm:

```bash
$ clang --target=wasm32 -Wno-incompatible-library-redeclaration -I/opt/wasm/include -nostdlib -c myprogram.c
$ wasm-ld --no-entry --export-all -L/opt/wasm/lib myprogram.o -lc-wasm -o myprogram.wasm
```


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
* NULL
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
* clearerr
* exit
* feof
* ferror
* fflush
* fgetc
* fileno
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
* printf
* putc
* realloc
* sbrk
* snprintf
* strcasecmp
* strcmp
* strlen
* strncasecmp
* strncmp
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
