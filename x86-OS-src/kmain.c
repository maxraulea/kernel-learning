#include "write_framebuffer.h"

int sum_of_three(int arg1, int arg2, int arg3)
{
	return arg1 + arg2 + arg3;
}

void kmain(){
	write_to_framebuffer(0, 0);
}
