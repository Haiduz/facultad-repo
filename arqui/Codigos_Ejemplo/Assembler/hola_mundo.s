.data
str: .asciz "Hola mundo"
    
.text
.global main
main:
	pushq %rbp
	movq $str, %rdi
	xor	%eax, %eax
	call printf
	xor	%eax, %eax
	popq %rbp
	ret