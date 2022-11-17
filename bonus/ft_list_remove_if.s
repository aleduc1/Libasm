bits 64
cpu x64
default rel
default nobnd
extern free
global ft_list_remove_if:function

; ToDo remove, this is just debug code to move somewhere and make sure we reached the correct destination
;section .data
;msg db 'hiiiiiiiii'
;len equ $ - msg
;mov rdi, 1
;mov rsi, msg
;mov rdx, len
;mov rax, 1
;syscall
;jmp end


; This function is mainly 3 big steps for handling the 3 main cases of node removal =>
; Case where we need to delete the first x beginning
; Case where we need to delete either in the middle or the last without the one before it
; Case where we deleted the penultimate and we still have to delete the last
section .text
ft_list_remove_if: ; return void
push rbp ; Preserve caller stack frame
;sub rsp, 8
;and rsp, 0xFFFF_FFFF_FFFF_FFF0 ; Align stack ToDo decomment after first try

; Step 1 -> Data saving in callee_saved
lea rbx, [rdi]; rdi = t_list **begin_list
mov r12, rsi	; rsi = void *data_ref
mov r13, rdx	; rdx = int (*cmp)()
mov r14, [rdi]; ptr = *begin_list
xor rbp, rbp	; tmp, we dont care about a stack frame anyway

; Step 2 -> 1st case
jmp loop1entry
free_first:
	mov rbp, r14 ; tmp = ptr
	mov r14, [r14 + 8] ; ptr = ptr->next
	mov BYTE [rbp + 8], 0 ; tmp->next = NULL
	mov rdi, [rbp] ; free(tmp->data)
	call free WRT ..plt
	mov rdi, rbp ; free(tmp)
	call free WRT ..plt
loop1entry:
	cmp r14, 0 ; while ptr, first condition
	jz step3
	mov rdi, [r14] ; ptr->data
	mov rsi, r12 ; Useless first turn tho
	call rdx
	cmp rax, 0 ; while cmp(data, data_ref), second condition
	jz free_first


; Step 3 -> 2nd case
step3:

mov [rbx], r14 ; *begin_list = ptr
xor rbp, rbp ; tmp = NULL

; Step 4 -> 3nd case
step4:

end:
leave
ret
