.data

.text
.global main
main:
	movq $1, %rax
	movq $3, %rdx

	#quiero que rax=3, rdx=1

	#pushq %rax #=> 1 rsp-=8, *rsp=1
	#pushq %rdx #=> 3

	#subq $8,%rsp
	#movq %rax,(%rsp)
	#subq $8,%rsp
	#movq %rdx,(%rsp)

	#movq %rax,-8(%rsp)
	#movq %rdx,-16(%rsp)
	#subq $16,%rsp

	subq $16,%rsp
	movq %rax,8(%rsp)
	movq %rdx,(%rsp)

	#No me interesa lo que quedó en la pila, no quiero usar/perder un registro
	#necesito que rsp quede como estaba
	addq $16,%rsp

	ret
