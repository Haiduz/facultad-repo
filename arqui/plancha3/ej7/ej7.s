.global main
    main:
    movq $0x0, %rax
    movq $0x0 , %rbx
    addq $0xFFFFFFFF, %rax
    addq $0xFFFFFFFF00000000 , %rbx
ret
