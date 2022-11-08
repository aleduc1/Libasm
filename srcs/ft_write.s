bits 64										; Uneeded since nasm -f elf64 enable it by default, just for me to know
cpu x64										; Dont enable opcode instructions that arnt compatible with x64 arch
default rel								; Enable RIP relative addressing by default, override with abs prefix
default nobnd							; Noop when MPX is unsupported but since its been drop id rather not
global ft_write:function	; function is an ELF specific extension to the global directive

section .data
	msg db "Hello world!", `\n`, `\0` ; String constant in backquotes support C-style escape char
	msglen equ $-msg	;$ refers to current address, - the address of the beginning of msg

section .text
ft_write:
	push rbp ; prologue, create a local stack for callee (ft_write when used independely)
	mov	rbp, rsp ; enter instruction exist to replace those first 3 lines but is slower
	sub	rsp, 0x10

	mov rax, 1 ; sys_write, args orde in register define by ABI64 calling conventions
	mov rdi, 1
	mov rsi, msg
	mov rdx, msglen
	syscall	;x86_64 native instruction instead of old interruptions

	mov rax, 60 ; sys_exit
	xor rdi, rdi ; most common way to reset a register value to 0
	syscall
end: ;Epilogue, stack reset
	leave ; enter counterpart, but actually used by gcc so fast => esp = ebp and pop ebp
	ret ; Basically pop rip
