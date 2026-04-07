.data
str: .asciz "%d\n"
a: .long 1234

.text
.global main
main:
    movq $str, %rdi
    movl a, %esi	
	movl $0, %eax
	call printf
	ret