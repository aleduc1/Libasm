bits 64
cpu x64
default rel
default nobnd
extern malloc
global ft_list_remove_if:function


; return = void
; rdi = t_list **head
; rsi = void *data_ref
; rdx = int (*cmp)()

section .text
ft_list_remove_if:

end:
ret
