.global main
main: 
    movq $0, %rax                    # RAX = 0x0000000000000000
    movq $0xAAAAAAA, %rbx            # RBX = 0x00000000AAAAAAA

    # hace 32 shift a la izquierda 
    shlq $32, %rbx                   # RBX = 0xAAAAAAA00000000
    # trivial

    orq  %rbx, %rax                  # RAX = 0xAAAAAAA00000000
    
    movq $0x55555555, %rbx           # RBX = 0x0000000055555555
    orq  %rbx, %rax                  # RAX = 0xAAAAAAA55555555


# porque no me imprime los 64 bits cuando intento imprimir rax en gdb?
# porque trunca los resultados, se asume que los 32 bits superiores son cero

# siempre al operar los 32 bits inferiores, los superiores 32 se setean en cero

# lo que hiciste aca no tiene mucho sentido, hubieses cargado directamente