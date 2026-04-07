.global main
    main:
    movq $0x1122334455667788, %rax
    addq $0x1122334455667788, %rax # rax -> 64 bits 
    ret

# sucede que assembly puede operar de inmediato 32 bits, por lo que para hacer 
# esta suma habria que hacerlo en dos pasos 
