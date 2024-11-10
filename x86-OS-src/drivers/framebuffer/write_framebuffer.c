#include "write_framebuffer.h"
#include <asm/io.h>
/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_CHAR_WIDTH 80
#define FB_CHAR_HEIGHT 25

#define FB_ADDR 0x000B8000



/** fb_write_cell:

*  Writes a character with the given foreground and background to position i
*  in the framebuffer.
*
*  @param i  The location in the framebuffer
*  @param c  The character
*  @param fg The foreground color
*  @param bg The background color
*/
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	char *fb = (char *) FB_ADDR;
	fb[i] = c;
	fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/** fb_move_cursor:
*  Moves the cursor of the framebuffer to the given position
*
*  @param pos The new position of the cursor
*/
void fb_move_cursor(unsigned short pos)
{
    outb(FB_HIGH_BYTE_COMMAND, FB_COMMAND_PORT);
    outb((pos >> 8) & 0x00FF, FB_DATA_PORT);
    outb(FB_LOW_BYTE_COMMAND, FB_COMMAND_PORT);
    outb(pos & 0x00FF, FB_DATA_PORT);
}

/* TODO can be optimized for using int* instead if char* */
void scroll()
{

	int* fb = (int*) FB_ADDR;
	
	for(unsigned int i = 0; i < FB_CHAR_HEIGHT; i++)
	{	
		for(unsigned int j = 0; j < FB_CHAR_WIDTH / 2; j++)
		{		
			int fb_old = j + i * FB_CHAR_WIDTH / 2;
			int fb_new = j + (i + 1) * FB_CHAR_WIDTH / 2;
			fb[fb_old] = fb[fb_new];
		}	
	}
	
	for(unsigned int i = 0; i < FB_CHAR_WIDTH; i++){
		int last_row_index = FB_CHAR_WIDTH * (FB_CHAR_HEIGHT) + i;
		fb[last_row_index] = 0x00;
	}
	// set the lowest row to 0
}

void write_to_framebuffer(char* buf, unsigned int len)
{	
	static unsigned int framebuffer_index = 0;
	
	for(unsigned int i = 0; i < len; i++)
	{
		if(buf[i] == '\n')
		{
			unsigned int char_till_end_line = 80 - (framebuffer_index % FB_CHAR_WIDTH);
			framebuffer_index += char_till_end_line;
			continue;
		}
		// we check if the frame buffer will enter the region out of the screen
		// then we have to shift the memory one row up and set the lowest line to 0
		if(framebuffer_index >= FB_CHAR_WIDTH * FB_CHAR_HEIGHT)
		{
			scroll();
			framebuffer_index = FB_CHAR_WIDTH * (FB_CHAR_HEIGHT - 1);	
		}	
		
		fb_write_cell(framebuffer_index * 2, buf[i], 2, 0);
		fb_move_cursor(framebuffer_index + 1);
		framebuffer_index++;
	}
}
