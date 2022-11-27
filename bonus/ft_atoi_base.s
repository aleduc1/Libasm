bits 64
cpu x64
default rel
default nobnd
global ft_atoi_base:function

section .text
ft_atoi_base:
push rbp
mov rbp, rsp
sub rsp, 8

; Save Callee saved that i use
push rbx
push r14
push r13
push r12
push r11

xor rax, rax ; Result
xor rbx, rbx ; Sign
xor rcx, rcx ; Str offset
xor r11, r11 ; Base offset
xor r12, r12 ; Base
xor r13, r13 ; tmp
xor r14, r14 ; current

jmp check_base_error
	inc_base_counter:
inc r11
	check_base_error: ; check that str_base is a base 10 number
cmp BYTE [rsi + r11], 0 ; while(to_check[i])
jle check_correct_size
cmp BYTE [rsi + r11], 48 ; str[i] > 0
jle return
cmp BYTE [rsi + r11], 57 ; str[i] < 9
jg return
jmp inc_base_counter

	check_correct_size: ; Check that base_str is 1 or 2 byte
cmp r11, 0 ; i < 0
jle return
cmp r11, 2 ; i > 2
jg return
xor r11, r11

	get_base: ; Store base as an int in r12
cmp BYTE [rsi + r11], 0 ; while(str_base[i])
je verify_base
imul r12, 10 ; base = base * 10
mov r13b, BYTE [rsi + r11] ; base + rsi
sub r13b, 48 ; base + rsi - 48
add r12b, r13b ; base = base + rsi - 48
inc r11
jmp get_base

	verify_base: ; Only accept base [2 - 16]
cmp r12, 2
jl return
cmp r12, 16
jg return

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

	handle_sign:
cmp	BYTE [rdi + rcx], 43 ; '+'
jz	inc_plus_sign
cmp	BYTE [rdi + rcx], 45 ; '-'
jz	inc_minus_sign
jmp	get_current_int
	inc_plus_sign:
inc rcx
jmp get_current_int
	inc_minus_sign:
inc rbx
inc rcx

	get_current_int:
xor r13, r13 ; Reset tmp register
cmp	BYTE [rdi + rcx], 48	; '0'
jl get_current_lower
cmp	BYTE [rdi + rcx], 57	; '9'
jg get_current_lower
mov r13b, BYTE [rdi + rcx] ; current char
sub r13b, 48 ; current char - 48
mov r14b, r13b ; r14 = current_int
jmp set_ret_value

	get_current_lower:
cmp	BYTE [rdi + rcx], 97	; 'a'
jl get_current_caps
cmp	BYTE [rdi + rcx], 122	; 'z'
jg get_current_caps
mov r13b, BYTE [rdi + rcx] ; current char
sub r13b, 87 ; current char - 'a' + 10
mov r14b, r13b ; r14 = current_int
jmp set_ret_value

	get_current_caps:
cmp	BYTE [rdi + rcx], 65	; 'A'
jl wrong_char
cmp	BYTE [rdi + rcx], 90	; 'Z'
jg wrong_char
mov r13b, BYTE [rdi + rcx] ; current char
sub r13b, 55 ; current char - 'A' + 10
mov r14b, r13b ; r14 = current_int
jmp set_ret_value
	
	wrong_char: ; We can be here either at the end of the parsed number or if a char in str is wrong
cmp rax, 0 ; If we already have smth to return dont mess with rbx and return it
jnz put_sign_back ; If this first char that isnt a sign is NAN we return 0
mov r14, -1
xor rbx, rbx ; so we dont negate the 0 if he sent -. but its unecessary prob

	set_ret_value:
cmp	r14, 0
jl	put_sign_back
cmp	r14, r12
jg	put_sign_back
imul rax, r12 ; rax = rax * base
add rax, r14 ; rax = rax + current
inc rcx
jmp get_current_int

	put_sign_back:
cmp	rbx, 0
jz return
neg rax

	return:
pop r11
pop r12
pop r13
pop r14
pop rbx
leave
ret
