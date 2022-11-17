bits 64
cpu x64
default rel
default nobnd
global ft_list_size:function

ft_list_size:
xor	rax, rax ; Standard says c register to count but here the count is the return value

loopbody:
cmp		rdi, 0
je		end
lea		rdi, [rdi + 8]
inc		rax
jmp		loopbody

end:
ret
