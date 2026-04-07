.data
f: .float 0.1
str: .asciz "%f\n"

.text
.global main
main:
    pushq %rbp
    movq $str, %rdi
    movss f, %xmm0
    cvtss2sd %xmm0, %xmm0
    movb $1, %al
    call printf
	xor	%eax, %eax
	popq %rbp
	ret