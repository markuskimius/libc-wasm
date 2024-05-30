BINARIES=atoi sizeof limits cat


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

sizeof.o: ../wasm/sizeof.c

limits.o: ../wasm/limits.c

cat.o: ../wasm/cat.c


# vim:noet:
