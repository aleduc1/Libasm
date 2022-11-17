bits 64
cpu x64
default rel
default nobnd
extern malloc
global ft_list_push_front:function

; toDo check if directives above need to be applied to every function given that we will then archive it into a static lib and link our program with the whole lib, is one nasm file enough to write those ?

section .text
ft_list_push_front:
mov rbx, rdi ; rbx is callee_saved, save **head
mov r12, rsi ; Save data in callee_saved reg

; malloc the new elem
mov rdi, 16 ; sizeof(t_list) = 16 in x64
call malloc WRT ..plt
test rax, rax
jle end
mov [rax], r12 ; new->data = data_arg
mov r13, [rbx] ; new->next = rbx, 2 lines
mov [rax + 8], r13
mov [rbx], rax ; *list = new

end:
ret
