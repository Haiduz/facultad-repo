.data
a: .float 1.0, -2.0
str: .asciz "%f\n"

.text
.global main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16,%rsp

    movl $4, -4(%rbp)   # m
    movl $10, -8(%rbp)   # k

    # Primera conversión
    movl -4(%rbp), %edi
    movss a, %xmm0
    movl -8(%rbp), %esi

    call convert

    movq $str, %rdi
    movl $1, %eax
    cvtss2sd %xmm0, %xmm0
    call printf

    # Segunda conversión
    movl -4(%rbp), %edi
    movss a+4, %xmm0
    movl -8(%rbp), %esi

    call convert

    movq $str, %rdi
    movl $1, %eax
    cvtss2sd %xmm0, %xmm0
    call printf

    movq %rbp, %rsp
    popq %rbp
    ret



