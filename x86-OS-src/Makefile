OBJECTS = loader.o io.o kmain.o write_framebuffer.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
MAKE = make

LDFLAGS = -T link.ld -melf_i386
AS = nasm
AR = ar
ASFLAGS = -f elf
DRIVERS = 0
LIBS = lib/lib.a
DRIVER_ARCHIVE = drivers/drivers.a
OBJECTS  = boot/loader.o io.o init/kmain.o 

all: kernel.elf

kernel.elf: lib drivers $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) $(DRIVER_ARCHIVE) $(LIBS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
                    -b boot/grub/stage2_eltorito    \
                    -no-emul-boot                   \
                    -boot-load-size 4               \
                    -A os                           \
                    -input-charset utf8             \
                    -quiet                          \
                    -boot-info-table                \
                    -o os.iso                       \
                    iso

run: os.iso
	qemu-system-i386 \
    		-m 32 \
    		-cdrom os.iso \
    		-boot d \
    		-monitor stdio        

run-mac: 
	qemu-system-i386 \
    		-m 32 \
    		-cdrom os.iso \
    		-boot d \
    		-monitor stdio        

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@
lib:
	$(MAKE) -C lib CC="$(CC)" CFLAGS="$(CFLAGS)" AR="$(AR)" clean all

drivers:
	$(MAKE) -C drivers CC="$(CC)" CFLAGS="$(CFLAGS)" clean all

clean:
	rm -rf *.o kernel.elf os.iso
	$(MAKE) -C lib clean
	$(MAKE) -C drivers clean

.PHONY: clean lib drivers
