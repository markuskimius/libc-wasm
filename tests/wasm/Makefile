BINARIES=asm.wasm alloc.wasm asprintf.wasm assert.wasm atof.wasm atoi.wasm cat.wasm ctype.wasm error.wasm exit.wasm heap.wasm isprint.wasm limits.wasm main.wasm math.wasm pow.wasm printf.wasm sizeof.wasm string.wasm test.wasm version.wasm
PREFIX=../..
CC=clang
LD=wasm-ld
CPPFLAGS=-I$(PREFIX)/include --target=wasm32
LDFLAGS=-L$(PREFIX)/lib
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

asm.o: asm.c

alloc.o: alloc.c

asprintf.o: asprintf.c

assert.o: assert.c

atof.o: atof.c

atoi.o: atoi.c

cat.o: cat.c

ctype.o: ctype.c

error.o: error.c

exit.o: exit.c

heap.o: heap.c

isprint.o: isprint.c

limits.o: limits.c

main.o: main.c

math.o: math.c

pow.o: pow.c

printf.o: printf.c

sizeof.o: sizeof.c

string.o: string.c

test.o: test.c

version.o: version.c


# vim:noet:
