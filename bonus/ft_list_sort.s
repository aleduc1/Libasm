bits 64
cpu x64
default rel
default nobnd
global ft_list_sort:function

section .text
ft_list_sort: ; non leaf
push rbp
mov rbp, rsp
and rsp, 0xFFFF_FFFF_FFFF_FFF0

; Data saving in callee_saved
mov rbx, rdi	; rdi = begin_list
mov r13, rsi	; rsi = (*cmp)()
xor r11, r11	; tmp = 0, ABI -> r11 = temporary register so its great to use it for swaps only here
mov r12, [rdi]; ptr = *begin_list

jmp loopentry
swap:
	mov r11, [r12]			; tmp = ptr->data
	mov r14, [r12 + 8]	; ptr->next
	mov r15, [r14]			; ptr->next->data
	mov [r12], r15			; ptr->data = ptr->next->data
	mov r15, r11				; ptr->next->data = tmp
	mov r12, [rbx]			; ptr = *begin_list
	jmp loopentry

loopbody:
	mov rdi, [r12] ; ptr->data
	mov r11, [r12 + 8] ; ptr->next
	mov rsi, [r11] ; ptr->next->data
	call r13 ; assume clobber register di,si,11 after the call
	cmp rax, 0
	jg swap ; if cmp > 0
	mov r12, [r12 + 8] ; ptr = ptr->next

loopentry:
	cmp r12, 0 ; while ptr
	jz end
	cmp QWORD [r12 + 8], 0 ; while ptr->next
	jz end
	jmp loopbody

end:
leave
ret
