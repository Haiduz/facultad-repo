/*
El programa está usando los registros r1, r4 y r5.
Por lo tanto, es responsable de guardar/restaurar r1
*/
.data
str: .asciz "%d\n"

.text
.global main
main:
    MOV   r1, #0xaa
    MOV   r4, #30
    MOV   r5, #-12

    PUSH  {r1,lr}               @ Se preserva r1
    MOV   r0, r5                @ Configurar parámetro para llamada a función
    BL    abs                   @ Se llama a la función
    MOV   r5, r0                @ Salvar resultado
    POP   {r1,lr}               @ Restaurar r1

    BX     lr

abs:
    PUSH  {r4, r5}      @ Se preservan los registros calle saved
    MOV   r1, #0
    CMP   r0, r1        @ Compara parámetro en r0 con cero
    BGE   end           @ Si r0 es >= saltar
    MVN   r4, r0        @ Copiar su valor negado (bit a bit) a r4
    ADD   r5, r4, #1    @ Sumar 1 para tener el complemnto a dos en r5
    MOV   r0, r5        @ Valor de retorno en r0

    PUSH {r0,lr}
    MOV r1, r0
    LDR r0, =str
    BL printf
    POP {r0,lr}

end:
    POP   {r4, r5}      @ Restaurar registros
    BX    lr            @ Retornar
