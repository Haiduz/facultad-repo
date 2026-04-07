
//Este codigo suma los elementos de una arreglo

.data
array:  .word  1, 2, 3, 4, 5
result: .word  0

.text
.global main

main:
    // carga la direccion de 'array' en un registro
    ldr r0, =array

    // Inicializa la suma a 0
    mov r1, #0

loop:
    // carga un elemento del arreglo en r2
    ldr r2, [r0], #4

    // Suma el elemento a la suma
    add r1, r1, r2

    // Compara la direccion del elemento actual con el final del arreglo 
    ldr r3, =array + 20  // Asumiendo que cada elemento es de 4 bytes

    // Vuelve al comienzo del bucle si no se ha alcanzado el final del arreglo
    cmp r0, r3
    bne loop

    // guarda el resultado en memoria
    ldr r3, =result
    str r1, [r3]

    // retorno el resultado en r0
	mov r0, r1
    bx lr




	