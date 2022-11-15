bits 64
cpu x64
default rel
default nobnd
global ft_strcmp:function

section .text
ft_strcmp:
xor rax, rax	; reset some register to use and debug with clarity
xor rdx, rdx
xor rcx, rcx

jmp loopbody ; skip incrementing before first char has been checked

increment:
	lea rdi, [rdi + 1] ; Jump to next byte in the string and repeat
	lea rsi, [rsi + 1]

loopbody:
	mov BYTE al, [rdi] ; result is based around first arg so we can already put it in `a` register 
	mov BYTE cl, [rsi] ; we gotta move those 2 because we cant cmp rdi and rsi directly, and to do it byte per byte requires more effort
	cmp al, cl ; little endian arch so lowest byte of a string is first char
	jnz end ; When they stop being equal we already have an answer so dont touch a and c register and jump to the end

loopentry:
; if we're here al and cl were equal, just need to know if they are equal on their char or because they're both finished
	cmp al, 0 ; Check if they aint over
	jnz increment

end:
	sub rax, rcx ; What the cmp instruction does without setting it in rax, a < b because of ascii representation
	ret
