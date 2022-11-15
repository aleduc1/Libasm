; Directives ;
bits 64										; Uneeded since nasm -f elf64 enable it by default, just for me to know
cpu x64										; Dont enable opcode instructions that arnt compatible with x64 arch
default rel								; Enable RIP relative addressing by default, override with abs prefix
default nobnd							; Noop when MPX is unsupported but since its been dropped id rather not
extern __errno_location		; function that evaluate to errno address, Cf errno.h
global ft_write:function	; function is an ELF specific extension to the global directive
%define SYS_write 0x01		; Preprocessor directive, Cf /usr/include/syscall.h

; Executable segment, opcode mmemonics ;
section .text ; Dont need to create a local stack frame because red_zone + no local variables needed
ft_write: ; Like what the C implementation does, we write here a wrapper to the syscall write
	mov rax, SYS_write ; In rax + other register already set if ABI compliant
	syscall	; x86_64 native instruction instead of old interruption code
	test rax, rax ; bitwise AND on itself, test non zero and set SF if rax < 0
	js _error ; Jump if SF, there is no negative addresses in x86/x64
	ret ; Pop rip (return address left by caller via call instruction) and jump to it
_error:
	push rbp ; I actually do need a local stack frame here because i will move rsp to align it
	mov rbp, rsp ; Call will add 8 byte, breaking alignement, but i dont think i need sub 8 here
	neg rax	; Currently a negative errno, errno defines are only positive, neg does 2s complement
	mov r10, rax ; Save errno value
	and rsp, 0xFFFF_FFFF_FFFF_FFF0 ; Align next 16 bytes bondary for 64 bit registers
	call __errno_location WRT ..plt ; WRT plt CF nasmdoc v2.15.05 chapter 9.2.5
	mov qword [rax], r10 ; Store errno value in errno memory
	mov rax, -1	; Return value of our wrapper (man 2 write)
	leave ; Return the stack frame to how it was before the call
	ret
