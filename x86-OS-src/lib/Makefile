LIB_OBJS = string.o 

all: lib.a

lib.a: $(LIB_OBJS)
	$(AR) rcs lib.a $(LIB_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_OBJS) lib.a
