# 
# Welcome to GDB Online.
# GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
# C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
# Code, Compile, Run and Debug online from anywhere in world.
# 
# 
.data
.align 16
a: .long 1, 2, 3, 4
b: .long 1, 2, 3, 4

.text
.global main
main:
	movaps a, %xmm0
	movaps b, %xmm1
	addps %xmm0, %xmm1
	xor	%eax, %eax
	ret