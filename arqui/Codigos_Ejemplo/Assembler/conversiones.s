.text
.global main
main:
	xor	%eax, %eax
	xor	%edx, %edx
	movw $-34, %ax
    cwd                 # resultado en dx:ax
    
    xor	%eax, %eax
	xor	%edx, %edx
	movw $-34, %ax
    cwde                # resultado en eax
    
    xor	%eax, %eax
    movb $-45, %al      # al = 0xd3
    movsbq %al, %rax            # resultado en rax
    
    xor	%eax, %eax
    movb $-45, %al      # al = 0xd3
    movzbq %al, %rax            # resultado en rax
    
    movq $-1, %rax
    movb $-45, %al      # al = 0xd3
    movzbw %al, %ax
	xor	%eax, %eax
	ret

# cwtl Convert word in %ax to doubleword in %eax (sign-extended) 
# cltq Convert doubleword in %eax to quadword in %rax (sign-extended) 
# cqto Convert quadword in %rax to octoword in %rdx:%rax 