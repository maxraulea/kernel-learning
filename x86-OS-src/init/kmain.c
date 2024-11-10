#include <maxos/write_framebuffer.h>
#include <maxos/write_serial.h>
#include <stdarg.h>

void init_serial_port(void)
{
	serial_configure_baud_rate(3);
	serial_configure_line();
}

void kmain()
{
	init_serial_port();
	char hallo[] = "hallo";
	write_buffer_to_serial(hallo, 5);
	
	char message[] = "ik ben max";
	char message2[] = "\nlet's test what happens";
	char message3[] = "\n jo boys";
	for(unsigned int i = 0; i < 12; i++){
		write_to_framebuffer(message, 10);
		write_to_framebuffer(message2, 24);
		write_to_framebuffer(message3, 9);
	}
	write_to_framebuffer(message3, 9);
}
