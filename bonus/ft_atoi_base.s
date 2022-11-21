bits 64
cpu x64
default rel
default nobnd
global ft_atoi_base:function

; rdi = str to convert
; rsi = base specifier
section .text
ft_atoi_base:
push rbp
mov rbp, rsp
sub rsp, 8
push rcx
xor rax, rax
xor rcx, rcx ; Str offset, i
xor r11, r11 ; Base offset

check_base_error: ; check base is only str
	cmp	BYTE [rsi + r11], 43 ; '+'
	jz	return
	cmp	BYTE [rsi + r11], 45 ; '-'
	jz	return
	cmp BYTE [rsi + r11], 1 ; base < 2
	jle return
	cmp BYTE [rsi + r11], 16 ; base > 16
	jg return

xor r11, r11
jmp skip_space
inc_counter:
	inc	rcx
skip_space:
	cmp	BYTE [rdi + rcx], 9	; '\t'
	jz	inc_counter
	cmp	BYTE [rdi + rcx], 10 ; '\n'
	jz	inc_counter
	cmp	BYTE [rdi + rcx], 11 ; '\v'
	jz	inc_counter
	cmp	BYTE [rdi + rcx], 12 ; '\f'
	jz	inc_counter
	cmp	BYTE [rdi + rcx], 13 ; '\r'
	jz	inc_counter
	cmp	BYTE [rdi + rcx], 32 ; ' '
	jz	inc_counter

set_ret_value:
; mov	rax, rax
	cmp	rbx, 0
	jz return
	neg rax

return:
	pop rcx
	ret
