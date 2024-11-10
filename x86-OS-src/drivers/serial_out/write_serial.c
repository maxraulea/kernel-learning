#include <asm/io.h>

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
* all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
* order, but they start at different values.
*/

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
* Tells the serial port to expect first the highest 8 bits on the data port,
* then the lowest 8 bits will follow
*/
#define SERIAL_LINE_ENABLE_DLAB         0x80

/** serial_configure_baud_rate:
*  Sets the speed of the data being sent. The default speed of a serial
*  port is 115200 bits/s. The argument is a divisor of that number, hence
*  the resulting speed becomes (115200 / divisor) bits/s.
*
*  @param com      The COM port to configure
*  @param divisor  The divisor
*/
void serial_configure_baud_rate(unsigned short divisor)
{
	outb(SERIAL_LINE_ENABLE_DLAB, SERIAL_LINE_COMMAND_PORT(SERIAL_COM1_BASE));
	outb((divisor >> 8) & 0x00FF, SERIAL_DATA_PORT(SERIAL_COM1_BASE));
	outb(divisor & 0x00FF, SERIAL_DATA_PORT(SERIAL_COM1_BASE));
}

/** serial_configure_line:
*  Configures the line of the given serial port. The port is set to have a
*  data length of 8 bits, no parity bits, one stop bit and break control
*  disabled.
*
*  @param com  The serial port to configure
*/
void serial_configure_line(void)
{
	/* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
	 * Content: | d | b | prty  | s | dl  |
	 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
	 */
	outb(0x03, SERIAL_LINE_COMMAND_PORT(SERIAL_COM1_BASE));
}

/** is_transmit_empty:
*  Checks whether the transmit FIFO queue is empty or not for the given COM
*  port.
*
*  @param  com The COM port
*  @return 0 if the transmit FIFO queue is not empty
*          1 if the transmit FIFO queue is empty
*/
static int is_transmit_empty(void)
{
	/* 0x20 = 0010 0000 */
	return inb(SERIAL_LINE_STATUS_PORT(SERIAL_COM1_BASE)) & 0x20;
}

/*
 *
 */
static void write_serial(char a) 
{
   while (is_transmit_empty() == 0);
   outb(a, SERIAL_DATA_PORT(SERIAL_COM1_BASE));
}

/* this function writes a given buffer to the serial output
 *
 */
void write_buffer_to_serial(const char* buf, unsigned int len)
{
	for(unsigned int i = 0; i < len; i++){
		write_serial(buf[i]);
	}
}

