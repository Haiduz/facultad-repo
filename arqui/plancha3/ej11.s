/*
11) Implementar un programa en Assembler para invertir un arreglo de bytes de longitud
conocida usando el stack.
Ayuda: Esto puede ser logrado “apilando” los valores de a uno en el stack y luego 
ir “desapilando” en sentido inverso
*/
.data
    arreglo: .long 1,2,3,4
    tamano: .long 4
.text
.global main
main:
    movl tamano, %ecx
    movl $0, %ebx
apilar:
    movl arreglo(,%rbx,4), %eax
    pushq %rax
    incl %ebx
    loop apilar

    movl tamano, %ecx
    movl $0, %ebx
desapilar:
    popq %rax
    movl %eax, arreglo(,%rbx,4)
    incl %ebx
    loop desapilar


ret
