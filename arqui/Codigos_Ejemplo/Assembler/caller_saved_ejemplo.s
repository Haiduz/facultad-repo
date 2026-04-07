.data
str: .asciz "Resultado: %d\n"

.text
.global main
main:
        subq $8, %rsp
        movl $40, %eax
        addl $45, %eax
        movl %eax, %esi
        leaq  str, %rdi  # movq $str, %rdi
        xor     %eax, %eax
        pushq %rsi
        call printf
        xor %eax, %eax
        addq $8, %rsp
        ret
