.section .data
    # Definimos los números en complemento a 2 de 8 bits
    N1: .byte 100    # 01100100 en binario
    N2: .byte 120    # 01111000 en binario  
    N3: .byte -63    # 11000001 en binario (complemento a 2 de 63)
    N4: .byte -56    # 11001000 en binario (complemento a 2 de 56)
    N5: .byte -91    # 10100101 en binario (complemento a 2 de 91)

.section .text
.global main

main:
    movq $0, %rax
    movq $0, %rbx
    # ===========================================
    # a) S1 = N1 + N2
    # ===========================================
    movb N1, %al     # Cargar N1 = 100 en AL
    movb N2, %bl     # Cargar N2 = 120 en BL
    addb %bl, %al    # AL = AL + BL = 100 + 120 = 220
    
    # ===========================================
    # b) S2 = N3 + N4  
    # ===========================================
    movb N3, %cl     # Cargar N3 = -63 en CL
    movb N4, %dl     # Cargar N4 = -56 en DL
    addb %dl, %cl    # CL = CL + DL = -63 + (-56) = -119
    
    # ===========================================
    # c) S3 = N3 + N5
    # ===========================================
    movb N3, %al     # Cargar N3 = -63 en AL
    movb N5, %bl     # Cargar N5 = -91 en BL  
    addb %bl, %al    # AL = AL + BL = -63 + (-91) = -154
    
    # ===========================================
    # d) S4 = N2 - N4
    # ===========================================
    movb N2, %cl     # Cargar N2 = 120 en CL
    movb N4, %dl     # Cargar N4 = -56 en DL
    subb %dl, %cl    # CL = CL - DL = 120 - (-56) = 120 + 56 = 176
    
    # ===========================================
    # e) S5 = N5 - N2
    # ===========================================
    movb N5, %al     # Cargar N5 = -91 en AL
    movb N2, %bl     # Cargar N2 = 120 en BL
    subb %bl, %al    # AL = AL - BL = -91 - 120 = -211
    
    # ===========================================
    # Finalizar programa correctamente
    # ===========================================
    movq $60, %rax    # syscall exit (64-bit)
    movq $0, %rdi     # código de salida 0
    ret
