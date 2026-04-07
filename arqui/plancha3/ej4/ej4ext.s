.global main
main: 
    movq $0, %rax                    # RAX = 0x0000000000000000
    movq $0xAAAAAAA, %rbx            # RBX = 0x00000000AAAAAAA

    # hace 32 shift a la izquierda 
    shlq $32, %rbx                   # RBX = 0xAAAAAAA00000000
    # trivial
    orq  %rbx, %rax                  # RAX = 0xAAAAAAA00000000
    
    # rbx!=rax
    movq $0x55555555, %rbx           # RBX = 0x0000000055555555
    orq  %rbx, %rax                  # RAX = 0xAAAAAAA55555555


# porque no me imprime los 64 bits cuando intento imprimir rax en gdb?
# porque trunca los resultados, se asume que los 32 bits superiores son cero

# basicamente para poder usar la totalidad de los bits hay que usar or y una bitmask en cero

# ver el apunte de los sufijos y que representan siento que hay un error

# por ahora dejalo, despues fijate como hace para hacer que no se extienda el 0/1 de eax a rax
# mi intuicion me dice que con un and se resuelve