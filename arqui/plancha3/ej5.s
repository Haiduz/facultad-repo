.global main
    main:
    movq $0x1122334455667788, %rax
    # addq $0x1122334455667788, %rax -> error 
    # para solucionar esto ṕuedo sumar dos subregistros
    movq $0x1122334455667788, %rbx 
    addq %rax, %rbx 
    ret

# sucede que assembly puede operar de inmediato ($) 32 bits, por lo que para hacer 
# esta suma habria que hacerlo en dos pasos, usando dos subregistros, (una de las soluciones)


