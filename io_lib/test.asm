%include "lib.inc"
global _start

section .data
message: db "Exit test have passed!", 10

section .text
_start:
    mov rax, 1          ; rax contains systemcall for write
    mov rdi, 1          ; rdi contains file descriptor for stdout (1)
    mov rsi, message    ; rsi contains an address of string to output
    mov rdx, 23         ; rdx contains output string length
    syscall
    call exit