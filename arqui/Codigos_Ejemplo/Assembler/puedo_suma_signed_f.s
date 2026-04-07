#sumar dos signed shorts (valores de 2 bytes) e indicar con
#1 => si la suma es correcta (no hubo overflow)
#0 => si la suma es incorrecta (hubo overflow)

.global puedo_suma_signed
puedo_suma_signed:

#	movw $0x7ffe, %di
#	movw $1,      %si
	
	addw %di,%si
	jo nopuedo
	
	movq $1, %rax
	ret

nopuedo:
	xorq %rax,%rax
	ret
