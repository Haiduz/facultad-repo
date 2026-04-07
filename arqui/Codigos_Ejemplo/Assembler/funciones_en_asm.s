.data
str:   .asciz "La suma es: %d\n"

.text
.global main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movl    $5, -4(%rbp)
        movl    $10, -8(%rbp)
        movl    -8(%rbp), %edx
        movl    -4(%rbp), %eax
        movl    %edx, %esi
        movl    %eax, %edi
        call    suma
        movl    %eax, %esi
        movl    $str, %edi
        movl    $0, %eax
        call    printf
        movl    $0, %eax
        movq    %rbp, %rsp
        popq    %rbp
        ret
suma:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -4(%rbp)
        movl    %esi, -8(%rbp)
        movl    -4(%rbp), %edx
        movl    -8(%rbp), %eax
        addl    %edx, %eax
        popq    %rbp
        ret
