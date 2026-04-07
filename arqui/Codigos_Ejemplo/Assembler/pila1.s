.global main
main:

	movq $3,%rcx
	movq $2,%rbx

	# rcx*2 + rbx*6 + rcx + rbx , usar solo rax para calculos
        #   3*2 +   2*6 +  3  +  2   => 23

	#rcx * 2
	movq %rcx,%rax
	movq $2, %r8
	mulq %r8
	pushq %rax

	#rbx * 6
	movq %rbx,%rax
	movq $6, %r8
	mulq %r8
	pushq %rax
	
	movq %rcx, %rax
	addq %rbx, %rax

	popq %rcx
	addq %rcx, %rax

	popq %rcx
	addq %rcx, %rax

	ret
	
