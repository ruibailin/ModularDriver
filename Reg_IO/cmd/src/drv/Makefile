ifneq ($(KERNELRELEASE),)

obj-m :=reg_dev.o \
    reg_drv.o
reg_dev-objs =\
    ../../../src/drv/platform/device/device.o \
    ../../../src/drv/platform/device/module.o
reg_drv-objs =\
    ../../../src/drv/specific/ioctl/ioreg/io/map_read.o \
    ../../../src/drv/specific/ioctl/ioreg/io/map_write.o \
    ../../../src/drv/specific/ioctl/ioreg/cmd_read.o \
    ../../../src/drv/specific/ioctl/ioreg/cmd_write.o \
    ../../../src/drv/platform/driver/clock/clock.o \
    ../../../src/drv/platform/driver/file/ops/ioctl/ioctl.o \
    ../../../src/drv/platform/driver/file/ops/ops.o \
	../../../src/drv/platform/driver/file/file.o \
	../../../src/drv/platform/driver/interrupt/server.o \
	../../../src/drv/platform/driver/interrupt/client.o \
	../../../src/drv/platform/driver/power/powermanage.o \
	../../../src/drv/platform/driver/chrdev.o \
	../../../src/drv/platform/driver/driver.o \
	../../../src/drv/platform/driver/module.o 

	
else

-include arm32.mk

KDIR:= /lib/modules/$(KERNEL_NAME)/build

CDIR:= $(shell pwd)

all:

	make -C $(KDIR) M=$(CDIR) modules -I$(KERNEL_INCLUDE)
	
clean:
	rm -rf .*.omd *.o *.mod.o *.ko .tmp_versions Module.symvers .Makefile.swp modules.order

endif
