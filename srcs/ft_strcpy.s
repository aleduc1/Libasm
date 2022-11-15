bits 64
cpu x64
default rel
default nobnd
global ft_strcpy:function

section .text
ft_strcpy:
;cld
;loop:
;	movsb
;	cmp rsi, 0
;	jne loop
;ret


;xor rcx, rcx
;xor rdx, rdx
;
;loopbody:
;mov BYTE dl, [rsi + rcx]
;mov BYTE [rdi + rcx], dl
;inc rcx
;
;loopentry:
;cmp dl, 0
;jne loopbody
;
;mov rax, rdi
;ret

xor		rcx, rcx
xor		rdx, rdx
cmp		rsi, 0
jz		return
jmp		copy

increment:
inc		rcx

copy:
mov		dl, BYTE [rsi + rcx]
mov		BYTE [rdi + rcx], dl
cmp		dl, 0
jnz		increment

return:
mov		rax, rdi
ret
