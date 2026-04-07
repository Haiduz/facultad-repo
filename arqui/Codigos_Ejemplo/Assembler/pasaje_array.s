.data
A: .long 1, 2, 3, 4, 5

.text
.global main
main:
        subq    $40, %rsp
        movl    $1, (%rsp)
        movl    $2, 4(%rsp)
        movl    $3, 8(%rsp)
        movl    $4, 12(%rsp)
        movl    $5, 16(%rsp)
        movq    %rsp, %rsi
        movl    $A, %edi
        call    suma
        movl    %eax, 28(%rsp)
        movl    28(%rsp), %eax
        addq    $40, %rsp
        ret
suma:
        movq    %rdi, -8(%rsp)
        movq    %rsi, -16(%rsp)
        movq    -8(%rsp), %rax
        addq    $8, %rax
        movl    (%rax), %edx
        movq    -16(%rsp), %rax
        addq    $12, %rax
        movl    (%rax), %eax
        addl    %edx, %eax
        ret