BINARIES=printf.wasm atoi.wasm atof.wasm ctype.wasm sizeof.wasm limits.wasm string.wasm cat.wasm test.wasm
PREFIX=../..
CC=clang
LD=wasm-ld
CPPFLAGS=--target=wasm32 -Wno-incompatible-library-redeclaration -I$(PREFIX)/include -nostdlib
LDFLAGS=--no-entry --export-all -L$(PREFIX)/lib
LDLIBS=-lc-wasm


##############################################################################
# PHONIES

.PHONY: all clean

all: $(BINARIES)

clean:
	$(RM) $(BINARIES) *.o


##############################################################################
# RULES

%.wasm: %.o
	$(LD) $(LDFLAGS) $(TARGET_ARCH) $< $(LDLIBS) -o $@ && chmod a-x $@


##############################################################################
# SOURCES

printf.o: printf.c

atoi.o: atoi.c

atof.o: atof.c

ctype.o: ctype.c

sizeof.o: sizeof.c

limits.o: limits.c

string.o: string.c

cat.o: cat.c

test.o: test.c


# vim:noet:
