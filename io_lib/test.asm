%include "lib.inc"
global _start

section .data
success_string_length: db "success: string_length", 10, 0
fail_string_length: db "failed: string_length", 10, 0   ; 22 + null-terminator
message_string_char: db "If you see '$' char test have passed", 10, 0   ; $ = 0x24

section .text
_start:
    ; test call string_length
    mov rdi, fail_string_length ; set rdi string address ('string_length' argument)
    call string_length
    cmp rax, 22                 ; check counted string length be 22
    je .passed_string_length
        mov rdi, fail_string_length
        call print_string
        jmp .finish_string_length
    .passed_string_length:
        mov rdi, success_string_length
        call print_string
    .finish_string_length:
    ; test call string_char
    mov rdi, message_string_char
    call print_string
    mov rdi, 0x24               ; '$' = 0x24
    call print_char
    call print_newline
    mov rdi, 0x99
    call print_uint
    call print_newline
    call exit