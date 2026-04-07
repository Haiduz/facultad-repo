.global main
    main:
    # rotar se usa directamente sobre el tamaño del subregistro usado
    # no el registro completo

    movb $0b00001111, %ah  
    rorb $1, %ah # 1000 0111 

    movb $0b10000000, %ah 
    rolb $1, %ah # 0000 0001 := 1

ret

# la rotaciones funcionan y no tiene en cuenta las carry flags
# lo que sucede es que si los msb son ceros no los muestra en gdb   

# FUNCION ADC : adcS <operando fuente>, <operando destino> 
# resulta en : < operando destino = operando destino + operando origen + acarreo (CF) >

