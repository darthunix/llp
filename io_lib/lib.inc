exit:
    mov rax, 60     ; set rax "exit" syscall number (60)
    xor rdi, rdi    ; set rdi exit code (0)
    syscall         ; call it