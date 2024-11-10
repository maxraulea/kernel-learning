DRIVER_OBJS = framebuffer/write_framebuffer.o 

all: drivers.a

drivers.a: $(DRIVER_OBJS)
	$(AR) rcs drivers.a $(DRIVER_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(DRIVER_OBJS) drivers.a
