TARGET=main.wasm
PREFIX=../..
CC=clang
LD=wasm-ld
CPPFLAGS=--target=wasm32 -Wno-incompatible-library-redeclaration -I$(PREFIX)/include -nostdlib
LDFLAGS=--no-entry --export-all -L$(PREFIX)/lib
LDLIBS=-lc-wasm


##############################################################################
# PHONIES

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) *.o


##############################################################################
# MAIN

main.wasm: main.o
	$(LD) $(LDFLAGS) $(TARGET_ARCH) $< $(LDLIBS) -o $@ && chmod a-x $@

main.o: main.c


# vim:noet:
