.data
a: .long 45
    
.text
.global main
main:
	movq %rax, %rbx
    movl a, %ebx
    movb %bl, a
    movw $0xff, a
    movl $45, %eax
    xorq %rax, %rax
	ret