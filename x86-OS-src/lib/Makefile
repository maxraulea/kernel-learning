LIB_OBJS = string.o stdio.o 

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Iinclude -c
all: lib.a

lib.a: $(LIB_OBJS)
	$(AR) rcs lib.a $(LIB_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_OBJS) lib.a
