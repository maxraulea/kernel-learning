#ifndef write_serial_h
#define write_serial_h

void write_buffer_to_serial(const char* buf, unsigned int len);

void serial_configure_line(void);

void serial_configure_baud_rate(unsigned short divisor);
#endif
