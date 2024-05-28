.SILENT:

build := build
mjc := $(build)/mjc


.PHONY: all
all: mjc


.PHONY: mjc
mjc: $(mjc)
$(mjc):
	mkdir -p $(@D); \
	cmake -B $(build); \
	make -C $(build)


.PHONY: clean
clean:
	make -C $(build) clean


.PHONY: scrub
scrub:
	rm -rf $(build)
