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
    # ===========================================
    # a) S1 = N1 + N2
    # ===========================================
    movb N1, %al     # Cargar N1 = 100 en AL
    movb N2, %bl     # Cargar N2 = 120 en BL
    addb %bl, %al    # AL = AL + BL = 100 + 120 = 220
    
    # Análisis de banderas para S1:
    # - CF (Carry Flag): 0 (no hay acarreo fuera del bit 7)
    # - OF (Overflow Flag): 1 (OVERFLOW - dos números positivos dan resultado negativo)
    #   100 (01100100) + 120 (01111000) = 220 (11011100)
    #   Bit de signo cambió de 0 a 1 → Overflow
    
    # ===========================================
    # b) S2 = N3 + N4  
    # ===========================================
    movb N3, %cl     # Cargar N3 = -63 en CL
    movb N4, %dl     # Cargar N4 = -56 en DL
    addb %dl, %cl    # CL = CL + DL = -63 + (-56) = -119
    
    # Análisis de banderas para S2:
    # - CF (Carry Flag): 1 (hay acarreo fuera del bit 7)
    # - OF (Overflow Flag): 0 (NO OVERFLOW - dos números negativos dan resultado negativo)
    #   -63 (11000001) + -56 (11001000) = -119 (10001001)
    #   Bit de signo se mantiene en 1 → Sin overflow
    
    # ===========================================
    # c) S3 = N3 + N5
    # ===========================================
    movb N3, %al     # Cargar N3 = -63 en AL
    movb N5, %bl     # Cargar N5 = -91 en BL  
    addb %bl, %al    # AL = AL + BL = -63 + (-91) = -154
    
    # Análisis de banderas para S3:
    # - CF (Carry Flag): 1 (hay acarreo fuera del bit 7)
    # - OF (Overflow Flag): 1 (OVERFLOW - resultado fuera de rango de 8 bits con signo)
    #   -63 (11000001) + -91 (10100101) = -154 (01100110) en 9 bits, pero en 8 bits: 01100110 = 102
    #   Dos números negativos dieron positivo → Overflow
    
    # ===========================================
    # d) S4 = N2 - N4
    # ===========================================
    movb N2, %cl     # Cargar N2 = 120 en CL
    movb N4, %dl     # Cargar N4 = -56 en DL
    subb %dl, %cl    # CL = CL - DL = 120 - (-56) = 120 + 56 = 176
    
    # Análisis de banderas para S4:
    # - CF (Carry Flag): 1 (en resta, CF=1 indica que hubo "borrow")
    # - OF (Overflow Flag): 1 (OVERFLOW - resultado fuera de rango)
    #   120 (01111000) - (-56) = 120 + 56 = 176 (10110000)
    #   Número positivo dio resultado con bit de signo 1 → Overflow
    
    # ===========================================
    # e) S5 = N5 - N2
    # ===========================================
    movb N5, %al     # Cargar N5 = -91 en AL
    movb N2, %bl     # Cargar N2 = 120 en BL
    subb %bl, %al    # AL = AL - BL = -91 - 120 = -211
    
    # Análisis de banderas para S5:
    # - CF (Carry Flag): 0 (en resta, CF=0 indica NO hubo "borrow" en el bit más significativo)
    # - OF (Overflow Flag): 1 (OVERFLOW - resultado fuera de rango de 8 bits con signo)
    #   -91 (10100101) - 120 (01111000) = -211 (00101101) en 9 bits, pero en 8 bits: 00101101 = 45
    #   Número negativo menos positivo dio positivo → Overflow
    
    # Finalizar programa
    mov $60, %rax    # syscall exit
    xor %rdi, %rdi   # código de salida 0
    syscall