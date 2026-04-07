.global convert
convert:
                            # El valor inmediato es la representacion de 1.8 según IEEE 754
    movq %rax, -8(%rsp)
    movsd -8(%rsp), %xmm1   # Carga el valor 1.8 en xmm1
    movq $32, %rax
    cvtsi2sdq %rax, %xmm2
                            # Carga el valor 32.0 convirtiendo el valor entero 32 de rax a xmm2
    mulsd %xmm1, %xmm0      # xmm0=xmm0*xmm1 => xmm0=t*1.8
    addsd %xmm2, %xmm0      # xmmo=xmm0+xmm2 => xmmo=t*1.8+32
                            # como el valor de retorno se escribe en xmm0 hemos terminado
    ret


