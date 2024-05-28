.PHONY: all clean install uninstall

all:
	make -C src all install
	make -C tests all

clean:
	make -C src clean
	make -C tests clean

install:
	make -C src install

uninstall:
	make -C src uninstall


# vim:noet:
