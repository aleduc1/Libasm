bits 64										; Uneeded since nasm -f elf64 enable it by default, just for me to know
cpu x64										; Dont enable opcode instructions that arnt compatible with x64 arch
default rel								; Enable RIP relative addressing by default, override with abs prefix
default nobnd							; Noop when MPX is unsupported but since its been dropped id rather not
extern __errno_location		; function that evaluate to errno address, Cf errno.h
global ft_write:function	; function is an ELF specific extension to the global directive
%define SYS_write 0x01		; Preprocessor directive, Cf /usr/include/syscall.h

section .text ;dont need to create a local stack frame because x64 + no local variables needed
ft_write: ; Like what the C implementation does, we write here a wrapper to the syscall write
	mov rax, SYS_write ; in rax + other register already set if ABI compliant
	syscall	; x86_64 native instruction instead of old interruption code
	test rax, rax ; only check last bit because no negative in x64
	js _error
	ret ; Pop rip (return address left by caller via call instruction) and jump to it
_error:
	neg rax	; On linux systems -1 | -4095 are reverse errno value indicating an error on most syscall
	mov r10, rax ; Save errno value
	call __errno_location WRT ..plt; WRT plt CF nasmdoc v2.15.05 chapter 9.2.5
	mov qword [rax], r10 ; Store errno value in errno memory
	mov rax, -1	; Return value of our wrapper (man 2 write)
	ret
