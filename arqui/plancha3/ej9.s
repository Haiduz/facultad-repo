.data
    a: .word -1
    # se encuentran dos bytes consecutivos, donde b es la direccion donde empiezan y 
    # bytes el primer byte contiene 0xaa y el segundo 99 
    b: .byte 0xaa, 99 
    c: .float 1.5 # 0x3FC00000
    str: .asciz "Hola mundo\n"
.text
.global main
main:
    leaq a, %rdx # se guarda en el registro %rdx la direccion de la etiqueta a 

    movw a, %ax    # ax = 0xffff
        # al = 0x63
    movl str, %esi    # esi = "aloH"
    movl c, %edi    # edi = 0x3fc00000
    movl %esi, ( %rdx)
ret

/*
    Etiqueta    Direccion   Valor 
    a           0x404010    0xff
                0x404011    0xff
    b           0x404012    0xaa
                0x404013    0x63
    c           0x404014    0x00
                0x404015    0x00
                0x404016    0xc0
                0x404017    0x3f
    str         0x404018    72  'H'
                0x404019    111 'o'
                0x404020    108 'l'
                0x404021    97  'a'
                0x404022    32  ' '
                0x404023    109 'm'
                0x404024    117 'u'
                0x404025    110 'n'
                0x404026    100 'd'
                0x404027    111 'o'
                0x404028    10  '\n'
                0x404029    0   '\000'
*/