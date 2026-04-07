.data

.text
.global main
main:
	movq $1, %rax
	movq $3, %rdx

	#quiero que rax=3, rdx=1

	#Esto no funciona: 
	#movq %rax,%rdx #rdx=1 => cambió el valor de rdx
	#movq %rdx,%rax #rax=1

	#pushq %rax #=> 1 rsp-=8, *rsp=1
	subq $8,%rsp
	movq %rax,(%rsp)

	#pushq %rdx #=> 3
	subq $8,%rsp
	movq %rdx,(%rsp) 

	#popq  %rax #<= 3
	movq (%rsp),%rax
	addq $8,%rsp

	#popq  %rdx #<= 1
	movq (%rsp),%rdx
	addq $8,%rsp

	#pushq %rax #=> apilar 1
	#movq %rdx,%rax #rax=3
	#popq %rdx      #rdx=1

#	pushq $10

	ret
