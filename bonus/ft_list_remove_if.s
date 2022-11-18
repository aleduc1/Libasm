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

; This function is mainly 3 steps for handling the 3 main cases of node removal =>
; Save data we will use for the function in callee_save register
; Case where we need to delete the first x beginning
; Case where we need to delete either in the middle or the last without the one before it
section .text
ft_list_remove_if: ; return void
push rbp ; Preserve caller stack frame
mov rbp, rsp ; Because non leaf
sub rsp, 40 ; Let 5 8byte value room on the stack, used to preserve callee_saved register we use
push rbx
push r12
push r13
push r14
push r15
and rsp, 0xFFFF_FFFF_FFFF_FFF0 ; Align stack, should be done but this cant hurt (i think) and act as a safety net

; Step 1 -> Data saving in callee_saved
mov rbx, rdi	; rdi = t_list **begin_list
mov r12, rsi	; rsi = void *data_ref
mov r14, [rdi]; ptr = *begin_list
xor r13, r13	; tmp
mov r15, rdx	; function pointer, otherwise after first call any function rdx is empty and we cant loop

; Step 2 -> 1st case
jmp loop1entry
free_first:
	mov r13, r14 ; tmp = ptr
	mov r14, [r14 + 8] ; ptr = ptr->next
	mov BYTE [r13 + 8], 0 ; tmp->next = NULL
	mov rdi, [r13] ; free(tmp->data)
	call free WRT ..plt
	mov rdi, r13 ; free(tmp)
	call free WRT ..plt
loop1entry:
	cmp r14, 0 ; while ptr, first condition
	jz step3
	mov rdi, [r14] ; ptr->data
	mov rsi, r12 ; Useless first turn tho
	call r15 ; Call cmp via callee_saved register
	cmp rax, 0 ; while cmp(data, data_ref), second condition
	jz free_first

; Step 3 -> 2nd case
step3:
mov [rbx], r14 ; *begin_list = ptr
xor r13, r13 ; tmp = NULL
jmp loop2entry
free_middle_last: ; Free the next and adjust ptr
	mov r13, [r14 + 8] ; tmp = ptr->next
	mov r11, [r13 + 8] ; ptr->next = tmp->next
	mov [r14 + 8], r11
	mov r14, [r14 + 8] ; ptr = ptr->next
	mov rdi, [r13] ; free(tmp->data)
	call free WRT ..plt
	mov rdi, r13 ; free(tmp)
	call free WRT ..plt
loop2entry:
	cmp r14, 0 ; while ptr, first condition
	jz end
	cmp QWORD [r14 + 8], 0 ; while ptr->next, second condition
	jz end
	mov r11, [r14 + 8] ; ptr->next
	mov rdi, [r11] ; ptr->next->data
	mov rsi, r12 ; data_ref
	call r15 ; Call cmp via callee_saved register
	cmp rax, 0 ; while cmp(next->data, data_ref), second condition
	jz free_middle_last ; free correct node if its the one we seek
	mov r14, [r14 + 8] ; ptr = ptr->next
	jmp loop2entry ; if its not loop again

end:
; Restore callee_save register that i used and restore stack frame, return to rip + 8
pop r15
pop r14
pop r13
pop r12
pop rbx
leave
ret
