BINARIES=atoi.wasm sizeof.wasm limits.wasm cat.wasm
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

atoi.o: atoi.c

sizeof.o: sizeof.c

limits.o: limits.c

cat.o: cat.c


# vim:noet:
