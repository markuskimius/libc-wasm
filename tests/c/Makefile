BINARIES=alloc alloc2 asprintf assert atof atoi cat ctype error exit isprint limits main math pow printf sizeof string test
# PREFIX=
# CC=
# LD=
# CPPFLAGS=
# LDFLAGS=
# LDLIBS=


##############################################################################
# PHONIES

.PHONY: all clean

all: $(BINARIES)

clean:
	$(RM) $(BINARIES) *.o


##############################################################################
# RULES

%.o: ../wasm/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<


##############################################################################
# SOURCES

alloc.o: ../wasm/alloc.c

alloc2.o: ../wasm/alloc2.c

asprintf.o: ../wasm/asprintf.c

assert.o: ../wasm/assert.c

atof.o: ../wasm/atof.c

atoi.o: ../wasm/atoi.c

cat.o: ../wasm/cat.c

ctype.o: ../wasm/ctype.c

error.o: ../wasm/error.c

exit.o: ../wasm/exit.c

isprint.o: ../wasm/isprint.c

limits.o: ../wasm/limits.c

main.o: ../wasm/main.c

math.o: ../wasm/math.c

pow.o: ../wasm/pow.c

printf.o: ../wasm/printf.c

sizeof.o: ../wasm/sizeof.c

string.o: ../wasm/string.c

test.o: ../wasm/test.c


# vim:noet:
