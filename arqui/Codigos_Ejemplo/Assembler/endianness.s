.data
a: .quad 0

.text
.global main
main:
    movq $0x1122334455667788, %rax
    movq %rax, a
    movb a, %al
    ret