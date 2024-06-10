BINARIES=asm.wasm atof.wasm atoi.wasm cat.wasm ctype.wasm exit.wasm limits.wasm printf.wasm sizeof.wasm string.wasm test.wasm
PREFIX=../..
CC=clang
LD=wasm-ld
CPPFLAGS=--target=wasm32 -Wno-incompatible-library-redeclaration -I$(PREFIX)/include -nostdlib
LDFLAGS=--no-entry --export-all -L$(PREFIX)/lib --import-memory
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

%.o: ../wasm/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<


##############################################################################
# SOURCES

asm.o: ../wasm/asm.c

atof.o: ../wasm/atof.c

atoi.o: ../wasm/atoi.c

cat.o: ../wasm/cat.c

ctype.o: ../wasm/ctype.c

exit.o: ../wasm/exit.c

limits.o: ../wasm/limits.c

printf.o: ../wasm/printf.c

sizeof.o: ../wasm/sizeof.c

string.o: ../wasm/string.c

test.o: ../wasm/test.c


# vim:noet:
