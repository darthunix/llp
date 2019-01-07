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
    mov rsi, rdi        ; set rsi string address to output string
    mov rdx, rax        ; set rdx output string length (from rax)
    mov rax, 1          ; set rax systemcall for write
    mov rdi, 1          ; set rdi file descriptor for stdout (1)
    syscall
    pop rdi             ; restore rdi register from stack
    ret

print_char:
    push rcx            ; save rcx (counter for print_uint)
    push rdi            ; save rdi whith char code on a stack
    mov rsi, rsp        ; set rsi char address from stack
    mov rdx, 1          ; set rdx output string length = 1
    mov rax, 1          ; set rax systemcall for write
    mov rdi, 1          ; set rdi file descriptor for stdout (1)
    syscall
    pop rdi             ; restore initial rdi (can be changed by call)
    pop rcx             ; restore rcx
    ret

print_newline:
    push rdi            ; save rdi on a stack
    mov rdi, 0xA        ; set rdi new line code
    call print_char
    pop rdi             ; restore rdi from stack
    ret

print_uint:
    xor rcx, rcx        ; set rcx zero (counter for remainders on stack)
    xor rdx, rdx        ; set rdx zero (remainder register)
    mov rax, rdi        ; set dividend register
    push rdi            ; save rdi on stack
    mov rbx, 10         ; set divider register to 10
    .loop_div:
        div rbx         ; divide rax by rbx
        add rdx, 0x30   ; conver remainder to ascii char code (4 -> 0x34)
        push rdx        ; save remainder as an ascii char code on stack
        inc rcx         ; increment stack counter
        cmp rax, rbx    ; if dividend is less than 10 - exit divide loop
        jle .end_div
        xor rdx, rdx    ; else clear rdx and jump into divide loop again
        jmp .loop_div
    .end_div:
        test rax, rax   ; if dividend is zero don't pring it (we want to output 9 but not 09)
        je .loop_print
        add rax, 0x30   ; convert the last dividend to ascii char code (4 -> 0x34)
        mov rdi, rax    ; call print_char
        call print_char
    .loop_print:
        cmp rcx, 0      ; untill counter is not decreased to zero
        je .end_print
        pop rdi         ; ... we pop remainders from stack
        call print_char ; ... and print them
        dec rcx         ; ... after that we decrease counter
        jmp .loop_print ; ... and jump into print loop again
    .end_print:
        pop rdi         ; restore rdi
        ret