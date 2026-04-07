.data
    a: .long 1, 2, 3, 4
    # direcc        value
    # 0x404018      0x00
    # 0x404019      0x00
    # 0x40401a      0X00
    # 0x40401b      0x01
    g: .quad 0x1122334455667788
    msg: .asciz "Imprime %c\n"
.text
.global main
main:
    # rbp = 0x7fffffffd580
    # rsp = 0x7fffffffd4e8 
    subq $8, %rsp # rsp = 0x7fffffffd4e0
    movq $g, %rax # rax = 0x404028
    movl g+4, %eax # rax = 0x11223344
    movq $3, %rbx # rbx = 0x3
    # ACA "A" ES "&A" 
    movb a(, %rbx,4), %al # carga 1 byte a partir de la direcc 
    # a + 3*4 , seria el 4to elemento de a -> al = 4 -> rax = 0x11223304 
    leaq msg, %rdi # rdi = 0x404030 = &msg
    movb ( %rdi, %rbx, 2), %sil # sil = msg[6] = 'e' = 101
    xorl %eax, %eax # rax = 0

    /*
    Segun la convencion de llamada a funcion del apunte
    %rdi  # 1er argumento
    %rsi  # 2do argumento  
    %rdx  # 3er argumento
    %rcx  # 4to argumento
    %r8   # 5to argumento
    %r9   # 6to argumento
    
    En este caso solo estan modificados los registros %rdi y %rsi 
    donde para printf %rdi guarda el mensaje y %rsi el elemento a reemplazar
    */
    call printf # "imprime e"
    addq $8, %rsp 
    ret

