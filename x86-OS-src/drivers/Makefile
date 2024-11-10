DRIVER_OBJS = framebuffer/write_framebuffer.o 

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -I../include -c
all: drivers.a

drivers.a: $(DRIVER_OBJS)
	$(AR) rcs drivers.a $(DRIVER_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(DRIVER_OBJS) drivers.a
