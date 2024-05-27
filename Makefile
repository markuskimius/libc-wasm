.PHONY: all clean install uninstall

all:
	make -C src all install
	make -C test all

clean:
	make -C src clean
	make -C test clean

install:
	make -C src install

uninstall:
	make -C src uninstall


# vim:noet:
