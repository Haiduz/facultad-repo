.data
str_1: .asciz "Cantidad de argumentos: %d\n"
str_2: .asciz "Primer argumento: %s\n"
.text
.global main
main:
prologo:
    pushq %rbp # Salvamos el registro rbp
    movq %rsp, %rbp # Usamos el registro rbp como puntero a la base del pila
    subq $16, %rsp # Reservamos espacio en la pila
    movq %rdi, -8(%rbp) # Guardamos el registro rdi en la pila
    movq %rsi, -16(%rbp) # Guardamos el registro rsi en la pila
imprime_numero:
    movq -8(%rbp), %rsi # rsi es el segundo argumento para llamar a printf
    movq $str_1, %rdi # rdi es el primer argumento para llamar a printf
    xorq %rax, %rax # La cantidad de argumentos de tipo vectorial es cero
    call printf # Llamamos a printf para imprimir el primer mensaje
imprime_primero:
    movq -16(%rbp), %rsi # Ahora en rsi tenemos la direcci´on del arreglo de punteros
    leaq 8(%rsi), %rax # Apuntamos al siguiente puntero
    movq (%rax), %rsi # dereferenciamos para tener la direcci´on de argv[1]
    movq $str_2, %rdi # rdi es el primer argumento para llamar a printf
    xorq %rax, %rax # La cantidad de argumentos de tipo vectorial es cero
    call printf # Volvemos a llamar a printf
epilogo:
    movq %rbp, %rsp # Restauramos el valor de rsp
    pop %rbp # Restauramos el valor de rbp
    ret # Finalmente retornamos
