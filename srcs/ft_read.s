bits 64										; Uneeded since nasm -f elf64 enable it by default, just for me to know
cpu x64										; Dont enable opcode instructions that arnt compatible with x64 arch
default rel								; Enable RIP relative addressing by default, override with abs prefix
default nobnd							; Noop when MPX is unsupported but since its been dropped id rather not
extern __errno_location		; function that evaluate to errno address, Cf errno.h
global ft_read:function		; function is an ELF specific extension to the global directive
%define SYS_read 0x0			; Preprocessor directive, Cf /usr/include/syscall.h

section .text
ft_read:
	mov rax, SYS_read
	syscall
	jc _error ; ToDo check this jc more in depth
	ret
_error:
; ToDo check if need to neg rax like write or not
	mov r10, rax
	call __errno_location WRT ..plt
	mov qword [rax], r10
	mov rax, -1
	ret
