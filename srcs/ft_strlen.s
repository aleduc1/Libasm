bits 64
cpu x64
default rel
default nobnd
global ft_strlen:function

section .text
ft_strlen:
xor rax, rax ; Usually rcx does count
je loopentry ; Loop inversion, kinda
loopbody: inc rax
loopentry: cmp BYTE [rdi + rax], 0
	jne loopbody
ret
