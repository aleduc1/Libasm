CPU x64
global ft_write:function

section .data
	msg db "Hello world!", `\n`, `\0`
	msglen equ $-msg	;$ refers to current address, - the address of the beginning of msg

section .text
ft_write:
	push rbp
	mov	rbp, rsp
	sub	rsp, 0x10
	mov rax, 1 ; sys_write
	mov rdi, 1 ; stdout, arg 1
	mov rsi, msg	; arg 2
	mov rdx, msglen	; arg 3
	syscall

	mov rax, 60 ; sys_exit
	xor rdi, rdi ; exit(0), arg1 space need to be put back to 0
	syscall
end:
	leave
	ret
