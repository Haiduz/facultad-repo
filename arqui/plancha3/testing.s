.section .data
    a: .asciz " Cant. de elementos: "
    b: .asciz "%d"
.text
.global main
main:
    # prologo
    pushq %rbp
    movq %rsp, %rbp

    # comienza el main
    call fc

    # epilogo
    movq %rbp, %rsp
    popq %rbp
ret

fc:
    # prologo
    pushq %rbp
    movq %rsp,%rbp
    
    # main de la fc
    subq $16, %rsp # alineo la pila a 16 bytes 

    movq $a, %rdi #a cargar la direccion del string !!
    xorl %eax, %eax
    call printf 

    movq $b, %rdi
    leaq -4(%rbp),%rsi # guardo en -4 el valor ingresado
    xorl %eax, %eax
    call scanf

    # ahora mismo en rax se encuentra el numero ingresado
    # quiero reservar en memoria un arreglo con la cant de enteros ingresados pero multiplos de 16
    
#    movl -4(%rbp), %eax 
    imull $4, %eax # cant de bytes necesarios

    # top(n/16) = ((n*4)+15) // 16 (div entera 16) 
    addl $15, %eax
    xorl %edx, %edx
    movl $16, %ebx
    idivl %ebx

    #reservo espacio en a memoria para ingresar luego
    imull $16, %eax 
    subq %rax, %rsp
    
    movq -4(%rbp), %rcx
    movq $0, -8(%rbp) # indice para el arreglo 
    
etiqueta:
    # la direccion a guardar seria array[i] = rsp + (i*4)
    # el iterador es -8(%rbp)
    movq $b, %rdi
    movq -8(%rbp), %rax     #rax = i 
    imulq $4, %rax          #rax = i*4
    leaq (%rsp, %rax), %rsi # rsi = &array[i]

    pushq %rcx
    pushq %rax 
    xorl %ecx, %ecx
    
    xorl %eax, %eax
    call scanf
    popq %rax
    popq %rcx
    incq -8(%rbp)
    loop etiqueta

    # epilogo
    movq %rbp, %rsp
    popq %rbp
ret 
