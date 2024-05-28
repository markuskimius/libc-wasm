TARGETS=c wasm


.PHONY: all clean install

all:
	@for i in $(TARGETS); do \
		echo make -C $$i;    \
		make -C $$i;         \
	done

clean:
	@for i in $(TARGETS); do    \
		echo make -C $$i clean; \
		make -C $$i clean;      \
	done


# vim:noet:
