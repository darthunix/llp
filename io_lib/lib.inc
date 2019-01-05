exit:
    mov rax, 60     ; set rax "exit" syscall number (60)
    xor rdi, rdi    ; set rdi exit code (0)
    syscall         ; call it

string_length:
    xor rax, rax    ; rax is a counter to hold string length. set rax 0
    .loop:
        cmp byte [rdi + rax], 0 ; pass first argument (string address) in rdi.
                                ; 'byte' is need as left and right side should be of the same size,
                                ; and the rigth side (zero) holds no info about its length.
                                ; use null-terminator (0) as an end of line.
        je .end
        inc rax     ; increment string length counter
        jmp .loop
    .end:
        ret         ; pop rip and finish call

print_string:
    push rdi            ; save rdi with string address on a stack (can be changed by call string_length)
    call string_length  ; put string length in rax
    pop rsi             ; restore string address from stack to rsi to output string
    mov rdx, rax        ; set rdx output string length (from rax)
    mov rax, 1          ; set rax systemcall for write
    mov rdi, 1          ; set rdi file descriptor for stdout (1)
    syscall
    mov rdi, rsi        ; restore rdi register
    ret

print_char:
    push rdi            ; save rdi whith char address on a stack
    mov rsi, rdi        ; set rsi char address
    mov rdx, 1          ; set rdx output string length = 1
    mov rax, 1          ; set rax systemcall for write
    mov rdi, 1          ; set rdi file descriptor for stdout (1)
    syscall
    pop rdi             ; restore initial rdi (can be changed by call)
    ret