#ifndef io_h
#define io_h

#define outb(value, port) \
	__asm__ ("outb %%al,%%dx"::"a" ((unsigned char)(value)),"d" ((unsigned short)(port)))

#endif
