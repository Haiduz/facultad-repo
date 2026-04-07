.global main
main:
    # pone la parte alta de rax en 0 y la parfe baja la llena de 1 o f 
    movl $-1, %eax 
    movl $2, %ecx # nada raro pasa aca 

    imull %ecx # [edx:eax = eax*ecx] => edx:eax = -1*2 = -2
    # C2(-2) = [edx] : 11 ... (32 veces) ... 11 [eax]: 11 ... (31 veces) 10 
    movq $-1, %rax
    movq $-1, %rcx
    imulq %rcx # [rdx:rax = rax*rcx] => rdx:rax = -1*-1 = 1 => rdx = 0 y rax = 1 (funca)
    
    # imullS <opernado fuente>, <operando destino> , es truncado y guardado en operando destino
    # truncado se refiere a que unicamente se guarda la parte baja
    
    imulw %cx, %ax # rax = -1 * 1 = -1 aca entra bien
    imulw $0x8000, %ax # -32768 * -1 = 32768, este numero necesita 17 bits para poder ser representado s 1 1000 0000 0000 0000
    # entonces en ax se guarda -32768 lo cual es un error 

    /*
    Digamos que para que el resultado quepa en el subregistro de rax debemos saber de antemano que entra alli
    recordemos con con signes las cotas son 2^(n-1) <= rango <= 2^(n-1) -1
    si sabemos que no entra podemos verificar si entra en rax y moverlo alli 
    */

    
    xorq %rax, %rax
    movw $-1, %ax
    movw $2, %cx
    mulw %cx
    # completar para que el resultado correcto como unsigned int
    # quede en eax
ret
