ARCHIVE:=libc-wasm.a
CC:=clang
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
	install -m 644 $(ARCHIVE) $(LIBDIR)
	@for i in *.h; do                              \
		echo install -m 644 $$i $(INCDIR); \
		install -m 644 $$i $(INCDIR);      \
	done

uninstall:
	$(RM) $(LIBDIR)/$(ARCHIVE)
	@for i in *.h; do                         \
		echo $(RM) $(INCDIR)/$$i;     \
		$(RM) $(INCDIR)/$$i;          \
	done
	rmdir -p $(INCDIR) || true
	rmdir -p $(LIBDIR) || true


##############################################################################
# ARCHIVE

libc-wasm.a: _start.o ctype.o errno.o math.o stdio.o stdlib.o string.o unistd.o
	llvm-ar rcs $@ $^


##############################################################################
# LIBRARY

_start.o: _start.c stdlib.h

ctype.o: ctype.c ctype.h

errno.o: errno.c errno.h

math.o: math.c math.h inttypes.h

stdio.o: stdio.c stdio.h errno.h math.h stdlib.h string.h unistd.h

stdlib.o: stdlib.c stdlib.h assert.h ctype.h string.h

string.o: string.c string.h ctype.h stdlib.h

unistd.o: unistd.c unistd.h

assert.h: stdio.h
	touch $@

stdio.h: inttypes.h
	touch $@

stdlib.h: inttypes.h
	touch $@

string.h: inttypes.h
	touch $@

unistd.h: inttypes.h
	touch $@


# vim:noet:
