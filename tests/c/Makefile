BINARIES=atof atoi cat ctype exit limits printf sizeof string test
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
