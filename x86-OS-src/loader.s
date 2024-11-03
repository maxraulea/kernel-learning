global loader				;the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002 		;magic number constant
FLAGS equ 0x0				;multiboot flags ??
CHECKSUM equ -MAGIC_NUMBER		;calculate the checksum should equal magic_number + checksum + flags = 0
KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes	

section .text:				;assembly code starts here
align 4					;the code must be 4 bytes alligned ?
	extern sum_of_three   ; the function sum_of_three is defined elsewhere
	dd MAGIC_NUMBER			;defining the constants
	dd FLAGS			;
	dd CHECKSUM			;	

loader:					;this is the entry point for the executable
	mov eax, 0xCAFEBABE		;place number in register eax
	mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the                                                ; stack (end of memory area)
	
	
	mov word [0x000B8000], 0x2841    	
	push dword 3            ; arg3
    	push dword 2            ; arg2
    	push dword 1            ; arg1
    	call sum_of_three       ; call the function, the result will be in eax
	mov al, 0x0D
	out  0x3D4, al      ; 14 tells the framebuffer to expect the highest 8 bits of the position
	mov al, 0x0F
	out 0x3D5, al    ; sending the highest 8 bits of 0x0050
	mov al, 15
	out 0x3D4, al      ; 15 tells the framebuffer to expect the lowest 8 bits of the position
	mov al, 0xFF
	out 0x3D5, al    ; sending the lowest 8 bits of 0x0050

.loop:
	jmp .loop			;infinite loop


section .bss
align 4
                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
        resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel
