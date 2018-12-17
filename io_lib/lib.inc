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