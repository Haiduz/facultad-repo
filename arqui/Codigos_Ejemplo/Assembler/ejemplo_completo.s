.data
a: .quad  0x1122334455667788
i: .long  0
f: .double 3.14
str: .asciz "Hola mundo"
	
.bss
b: .quad 
	
.text
.global main
main:
     movq a, %rax           # rax=0x1122334455667788
     movq $a, %rax          # dirección de a
     movl i, %ebx           # ebx=0 
     movq $-1, %rax         # rax=0xffffffffffffffff (-1)
     movq %rax, i       
     movq f, %rdx           # rdx=0x40091eb851eb851f (3.14)
     movl str, %ecx         # ecx=0x616c6f48 ("aloH")
	 leaq a, %rax           # dirección de a
	 leaq a+1, %rax         
	 retq