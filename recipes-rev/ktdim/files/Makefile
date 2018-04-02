EXTRA_CFLAGS := -I$(src) -DDEBUG -Werror
obj-m += ktdim.o
SRC := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install
