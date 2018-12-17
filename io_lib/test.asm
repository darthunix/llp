%include "lib.inc"
global _start

section .data
test_string_length: db "failed: string_length", 10, 0   ; 22 + null-terminator

section .text
_start:
    mov rdi, test_string_length ; set rdi string address ('string_length' argument)
    call string_length
    cmp rax, 22             ; check counted string length be 22
    je .end
    mov rdx, rax            ; set rdx output string length (stored in rax)
    mov rax, 1              ; set rax systemcall for write
    mov rdi, 1              ; set rdi file descriptor for stdout (1)
    mov rsi, test_string_length      ; set rsi an address of string to output
    syscall
    .end:
        call exit