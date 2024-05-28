TARGETS=c wasm


.PHONY: all clean install

all:
	@for i in $(TARGETS); do \
		make -C $$i;         \
	done

clean:
	@for i in $(TARGETS); do \
		make -C $$i clean;   \
	done


# vim:noet:
