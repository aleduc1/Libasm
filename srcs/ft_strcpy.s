bits 64
cpu x64
default rel
default nobnd
global ft_strcpy:function

section .text
ft_strcpy:
; First method that doesnt work, byte per byte approach
;xor rcx, rcx
;xor rdx, rdx
;
;loopbody:
;mov BYTE dl, [rsi + rcx]
;mov BYTE [rdi + rcx], dl
;cmp BYTE [rsi + rcx], 0 ; Increment after cmp because we want to copy the first 0 (man 3 strcpy)
;lea rcx, [rcx + 1] ; Need lea to increment without altering the rflags
;jne loopbody
;lea rax, [rdi]
;ret

; Second method that doesnt work, byte per byte approach
cld
lea rax, [rdi]
loop:
	movsb
	cmp BYTE [rsi], 0
	jne loop
movsb
ret
