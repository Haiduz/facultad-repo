.data
a: .quad 11, 22, 33, 44, 55
b: .quad 126
.text
.global main
main:
	movq a, %rax
	movq $a, %rbx
	movq (%rbx), %rax
	movq 8(%rbx), %rax
	movq $3, %rcx 
	movq (%rbx, %rcx, 8), %rax
	movq 8(%rbx, %rcx, 8), %rax
	leaq a, %rbx
	xor	%eax, %eax
	ret