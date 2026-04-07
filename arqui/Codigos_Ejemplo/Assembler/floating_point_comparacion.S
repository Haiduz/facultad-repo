.data
a: .float 2.0 
b: .float 4.0
c: .float 9.0

.text
.global main
main:
    movss a, %xmm0
    mulss b, %xmm0
    ucomiss c, %xmm0
    jbe menor_igual     # salta si a*b <= c
    movq $99, %rax
    jmp fin
menor_igual:
    movq $0, %rax
fin:
    ret