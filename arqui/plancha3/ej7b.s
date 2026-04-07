.text
.global main
main:
    # conisdero el registro 
    movq $0xaaaaaaaaaaaaaaaa, %rax
    movq $0, %rbx # contador en cero 
    # cantidad de veces q tengo que rotar el numero teniendo en cuenta la cf
    movq $65, %rcx 
    clc # limpia la carry flag
_loop:    
    # en caso de la carry flag sea cero, salta a la etiqueta add (no suma 1)
    jnc _add
    inc %rbx
_add:
    rclq %rax

    # decrementa rcx en 1 y salta a _loop siempre y cuando rcx sea distinto de cero 
    loop _loop 
ret