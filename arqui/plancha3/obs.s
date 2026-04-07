.global main
    main:
    movl $0, %eax
    movl $0, %ebx

    # Ejemplo que activa ambas flags
    movb $0xFF, %al     # AL = 255 unsigned, -1 signed
    addb $0x01, %al     # AL = 0x00 → CF=1 (unsigned overflow), OF=0 (signed ok)
    # literalmente -1+1 = 0 en signed 

    movb $0x7F, %bl     # BL = 127 unsigned, +127 signed  
    addb $0x01, %bl     # BL = 0x80 → CF=0 (unsigned ok), OF=1 (signed overflow)
ret 