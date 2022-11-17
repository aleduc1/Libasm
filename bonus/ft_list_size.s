bits 64
cpu x64
default rel
default nobnd
global ft_list_size:function

section .text
ft_list_size:
xor	rax, rax ; Standard says c register to count but here the count is the return value

loopbody:
cmp		rdi, 0
je		end
mov		rdi, [rdi + 8] ; lea doesnt work we need to access its value here
inc		rax
jmp		loopbody

end:
ret
