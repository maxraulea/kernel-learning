#ifndef io_h
#define io_h

#define outb(value, port) \
	__asm__ ("outb %%al,%%dx"::"a" ((unsigned char)(value)),"d" ((unsigned short)(port)))

#define inb(port) ({ \
unsigned char _v; \
__asm__ volatile ("inb %%dx,%%al":"=a" (_v):"d" (port)); \
_v; \
})

#endif
