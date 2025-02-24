ARCHIVE:=libc-wasm.a
CC:=clang
CFLAGS:=-mbulk-memory
CPPFLAGS:=-I. --target=wasm32 -g
PREFIX:=..
EPREFIX:=$(PREFIX)
LIBDIR:=$(EPREFIX)/lib
INCDIR:=$(PREFIX)/include


##############################################################################
# PHONIES

.PHONY: all clean install

all: $(ARCHIVE)

clean:
	$(RM) $(ARCHIVE) *.o

install: $(ARCHIVE)
	install -m 755 -d $(LIBDIR)
	install -m 755 -d $(INCDIR)
	install -m 755 -d $(INCDIR)/sys
	install -m 644 $(ARCHIVE) $(LIBDIR)
	@for i in *.h; do                          \
		echo install -m 644 $$i $(INCDIR);     \
		install -m 644 $$i $(INCDIR);          \
	done
	@for i in sys/*.h; do                      \
		echo install -m 644 $$i $(INCDIR)/sys; \
		install -m 644 $$i $(INCDIR)/sys;      \
	done

uninstall:
	$(RM) $(LIBDIR)/$(ARCHIVE)
	@for i in sys/*.h; do         \
		echo $(RM) $(INCDIR)/$$i; \
		$(RM) $(INCDIR)/$$i;      \
	done
	@for i in *.h; do             \
		echo $(RM) $(INCDIR)/$$i; \
		$(RM) $(INCDIR)/$$i;      \
	done
	rmdir -p $(INCDIR)/sys 2>/dev/null || true
	rmdir -p $(LIBDIR) 2>/dev/null || true


##############################################################################
# ARCHIVE

libc-wasm.a: _start.o ctype.o errno.o math.o stdio.o stdlib.o string.o unistd.o
	llvm-ar rcs $@ $^


##############################################################################
# LIBRARY

_start.o: _start.c stdlib.h

ctype.o: ctype.c ctype.h

errno.o: errno.c errno.h

math.o: math.c math.h stdio.h stdint.h

stdio.o: stdio.c stdio.h errno.h math.h stdint.h stdlib.h string.h unistd.h

stdlib.o: stdlib.c stdlib.h assert.h ctype.h errno.h limits.h math.h stdint.h string.h unistd.h

string.o: string.c string.h ctype.h errno.h stdint.h stdlib.h

unistd.o: unistd.c unistd.h

assert.h: stdio.h stdlib.h libc-wasm.h
	touch $@

ctype.h: libc-wasm.h
	touch $@

errno.h: libc-wasm.h
	touch $@

inttypes.h: stdint.h
	touch $@

limits.h: libc-wasm.h
	touch $@

math.h: libc-wasm.h
	touch $@

stddef.h: libc-wasm.h
	touch $@

stdint.h: libc-wasm.h
	touch $@

stdio.h: stddef.h libc-wasm.h
	touch $@

stdlib.h: stddef.h libc-wasm.h
	touch $@

string.h: stddef.h libc-wasm.h
	touch $@

unistd.h: stddef.h libc-wasm.h
	touch $@


# vim:noet:
