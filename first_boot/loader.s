global loader				;the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002 		;magic number constant
FLAGS equ 0x0				;multiboot flags ??
CHECKSUM equ -MAGIC_NUMBER		;calculate the checksum should equal magic_number + checksum + flags = 0

section .text:				;assembly code starts here
align 4					;the code must be 4 bytes alligned ?
	dd MAGIC_NUMBER			;defining the constants
	dd FLAGS			;
	dd CHECKSUM			;	

loader:					;this is the entry point for the executable
	mov eax, 0xCAFEBABE		;place number in register eax
.loop:
	jmp .loop			;infinite loop
