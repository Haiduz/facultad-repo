.data
str: .string "%d\n"

.text
.global main
main:
        push {ip, lr}   @ push return addres + dummy register para alineaciÃ³n
        ldr r0, =str    @ primer argumento
        mov r1, #45     @ segundo argumento
        bl printf       @ call printf
        mov r0, #0
        pop {ip, lr}
        bx lr
