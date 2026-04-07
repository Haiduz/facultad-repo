	.data
		.align 16
		a: .float 1.0, 2.0, 3.0, 4.0
		b: .float 1.0, 2.0, 3.0, 4.0
		
		.text
		.global main
		main:
		    movq $a, %rdi                   # rdi apunta a "a"
		    movq $b, %rsi                   # rsi apunta a "b"
		    movaps (%rdi), %xmm0            # copia los 4 floats de "a" a xmm0
		    movaps (%rsi), %xmm1            # copia los 4 floats de "b" a xmm1
		    addps %xmm0, %xmm1              # suma los 4 floats a la vez
		    movaps %xmm1, (%rdi)            # guarda el resultado en "a"
		    ret