bits 64

section .data
	msg db "Hello world!", 0x0a, 0
	len equ $-msg	;$ refers to current address, - the address of the beginning of msg

section .text
	global _start
_start:
	mov rax, 1 ; sys_write
	mov rdi, 1 ; stdout, arg 1
	mov rsi, msg	; arg 2
	mov rdx, len	; arg 3
	syscall

	mov rax, 60 ; sys_exit
	xor rdi, rdi ; exit(0), arg1 space need to be put back to 0
	syscall
