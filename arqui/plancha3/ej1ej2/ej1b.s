.global main
main:
    movb $0xFE, %al # no suma un byte? por el sufijo b
    movb $-1, %bl # 0xFF
    addb %bl, %al
    incb %bl # incrementa en 1
    ret
# asigna a %al 254 = 1111 1110 , despues a %bl le pone -1=1111 1111, luego
# addb hace la suma aritmetica donde se asigna %al = %bl + %al
# (b)%al = 1111 1110 + 1111 1111 = 1 1111 1101 (OF) 1111 1101  
# (u)%al = 254 + 255 = 509                     (OF) 253
# (s)%al = -1 + -2 = -3 (no carry flag entra bien)

# al incrementar en 1 %bl = 1111 1111 (CF) y te queda cero 
