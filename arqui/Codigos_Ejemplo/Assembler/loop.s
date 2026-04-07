.text
.global main
main:
	movq $0, %rax
	movl $10, %ecx      # cantidad de veces que se repetirá el bucle
my_loop:
    incq %rax           # cuerpo del loop
    loop my_loop
	xor	%eax, %eax
	ret