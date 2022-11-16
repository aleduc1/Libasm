bits 64
cpu x64
default rel
default nobnd
extern malloc
extern ft_strlen
extern ft_strcpy
global ft_strdup:function

section .data
msg db 'hello'
len equ $-msg

section .text
ft_strdup: ; Not efficient : call 2 fct
push rbp ; Save stack pointer
mov rbp, rsp ; Since non leaf

; get len of rdi (str)
mov rbx, rdi ; Save str, rbx is callee-saved
and rsp, 0xFFFF_FFFF_FFFF_FFF0 ; Align stack before first call
call ft_strlen

; Add one space for terminating 0
cmp rax, 0 ; Only if strlen != 0
jz _allocate
inc rax

; Malloc a new string of this size
_allocate:
mov rdi, rax
call malloc WRT ..plt ; I assume stack is still aligned
test rax, rax ; Set ZF and SF accordingly
jle _fail ; Check if malloc failed, .label is for local labels

; Cpy the param string into the newly allocated
mov rdi, rax
mov rsi, rbx
call ft_strcpy ; I assume stack is still aligned
jmp _epilogue

_fail: xor rax, rax ; Cf. man 3 strdup

_epilogue:
leave ; Restore the stack frame
ret ; Pop rip & jump
