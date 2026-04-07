.global main
main:
    movb $0xFF, %al
    ret 

# donde ".global main main:" son las etiquetas globales y la definicion de la funcion main
# "movb" tiene el sufijo b, que determina el tamaño de la operacion, ,en este caso es un byte
# instruccion mencionada es la instruccion generica para copiar un dato de un origen a un destino
# nuestro origen es la constante ($) 0xFF = 255  con destino a %al
# "%al"  es el subregistro de RAX (64 bits) → EAX (32 bits) → AX (16 bits) → AL (8 bits bajos) 