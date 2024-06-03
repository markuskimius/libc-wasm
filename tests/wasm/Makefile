BINARIES=atof.wasm atoi.wasm cat.wasm ctype.wasm limits.wasm printf.wasm sizeof.wasm string.wasm test.wasm
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

atof.o: atof.c

atoi.o: atoi.c

cat.o: cat.c

ctype.o: ctype.c

limits.o: limits.c

printf.o: printf.c

sizeof.o: sizeof.c

string.o: string.c

test.o: test.c


# vim:noet:
