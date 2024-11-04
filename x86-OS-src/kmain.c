#include "write_framebuffer.h"

int sum_of_three(int arg1, int arg2, int arg3)
{
	return arg1 + arg2 + arg3;
}

void kmain(){
	char message[] = "ik ben max";
	char message2[] = "\nlet's test what happens";
	//while(1){
		write_to_framebuffer(message, 10);
		write_to_framebuffer(message2, 24);
	//}
}
