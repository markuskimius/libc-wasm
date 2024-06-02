BINARIES=printf atoi atof ctype sizeof limits string cat test


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

printf.o: ../wasm/printf.c

atoi.o: ../wasm/atoi.c

atof.o: ../wasm/atof.c

ctype.o: ../wasm/ctype.c

sizeof.o: ../wasm/sizeof.c

limits.o: ../wasm/limits.c

string.o: ../wasm/string.c

cat.o: ../wasm/cat.c

test.o: ../wasm/test.c


# vim:noet:
