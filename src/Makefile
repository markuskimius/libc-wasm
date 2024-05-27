ARCHIVE=libc-wasm.a
CC=clang
CPPFLAGS=--target=wasm32 -Wno-incompatible-library-redeclaration -I. -nostdlib
PREFIX=..


##############################################################################
# PHONIES

.PHONY: all clean install

all: $(ARCHIVE)

clean:
	$(RM) $(ARCHIVE) *.o

install: $(ARCHIVE)
	install -m 755 -d $(PREFIX)/lib
	install -m 755 -d $(PREFIX)/include
	install -m 644 $(ARCHIVE) $(PREFIX)/lib
	@for i in *.h; do                         \
		install -m 644 $$i $(PREFIX)/include; \
	done

uninstall:
	$(RM) $(PREFIX)/lib/$(ARCHIVE)
	@for i in *.h; do                         \
		$(RM) $(PREFIX)/include/$$i;          \
	done
	rmdir $(PREFIX)/include
	rmdir $(PREFIX)/lib


##############################################################################
# ARCHIVE

libc-wasm.a: stdio.o stdlib.o string.o unistd.o errno.o
	llvm-ar rcs $@ $^


##############################################################################
# LIBRARY

stdio.o: stdio.c stdio.h unistd.h string.h errno.h

stdlib.o: stdlib.c stdlib.h assert.h

string.o: string.c string.h stdlib.h

unistd.o: unistd.c unistd.h

errno.o: errno.c errno.h

assert.h: stdio.h

stdio.h: inttypes.h
	touch $@

stdlib.h: inttypes.h
	touch $@

string.h: inttypes.h
	touch $@

unistd.h: inttypes.h
	touch $@


# vim:noet:
