bits 64
cpu x64
default rel
default nobnd
extern __errno_location
global ft_read:function
%define SYS_read 0x00

section .text
ft_read:
	mov rax, SYS_read
	syscall
	test rax, rax ; We can do jc directly after syscall in BSD based system since syscall set cf on
	js _error ; On error, but its not default everywhere so ill stick to this for now
	ret
_error:
	push rbp
	mov rbp, rsp
	neg rax
	mov r10, rax
	and rsp, 0xFFFF_FFFF_FFFF_FFF0
	call __errno_location WRT ..plt
	mov qword [rax], r10
	mov rax, -1
	leave
	ret
