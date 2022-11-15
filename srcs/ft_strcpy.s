bits 64
cpu x64
default rel
default nobnd
global ft_strcpy:function

section .text
ft_strcpy:
; First method with movsb, didnt do it the rep movsb method because it requires a call to len
cld ; To make sure we are moving rdi and rsi in the right direction
lea rax, [rdi]
loop:
	movsb ; Operand are optional since it already copies in correct places
	cmp BYTE [rsi], 0 ; Rsi act like an incrementing pointer in this case, we check on it directly
	jne loop
movsb ; For the terminating 0
ret

; Alternate method: byte per byte approach (untested but should work)
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
