/*
a) Implementar un programa en Assembler x86-64 para sumar el arreglo de n ́umeros
mostrado en la declaraci ́on de variables.
b) Actualice el programa de la pregunta anterior para encontrar el m ́aximo, el m ́ınimo y
el promedio del arreglo de n ́umeros.
c) Imprimir los resultados de los  ́ıtems anteriores por pantalla.
d) Modificar el  ́ıtem b) usando instrucciones de movimiento de datos condicionales (familia
de instrucciones CMOVcc, ver Manual de Intel).
Recomendaciones:
Realizar los c ́alculos requeridos en funciones separadas para que quede un c ́odigo claro y
ordenado.
*/

.section .data
    array: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
    length: .long 10
    min: .long 0x7FFFFFFF # maximo numero represetable  signed de 4 Bytes
    max: .long 0x80000000 # minimo numero representable signed de 4 Bytes   
.text
.global main
# i = lenght
# while(i != 0){
#   i--
#   if(array[i] >= max){
#   max = array[i]
#   }
#   if(arrat[i] < min){
#   min = array[i]
#   }
# }

main:
    movl length, %ecx
    movl $0, %ebx
ite:
    cmpl max, array(,%rbx,4)  # array[rcx] - max  
    jl not_max
    movl array(,%rbx,4), max  
not_max:
    cmpl min, array(,%rbx,4)
    jg not_min
    movl array(,%rbx,4), min
not_min:
    incl
    loop ite

ret
