BINARIES=atoi cat sizeof


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

atoi.o: ../wasm/atoi.c

cat.o: ../wasm/cat.c

sizeof.o: ../wasm/sizeof.c


# vim:noet:
