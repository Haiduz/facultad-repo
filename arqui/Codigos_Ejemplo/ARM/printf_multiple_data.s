.data
array: .word 1, 2, 3, 4, 5, 6
str: .asciz "%d %d %d %d %d %d\n"

.text
.global main
main:
        push {ip,lr}
        ldr r0, =str
        ldr r7, =array
        ldr r1, [r7]
        ldr r2, [r7,#4]
        ldr r3, [r7,#8]
        ldr r4, [r7,#12]
        ldr r5, [r7,#16]
        ldr r6, [r7,#20]
        push {r4-r6}
        bl printf
        pop {r4-r6}
        pop {ip,lr}
        bx lr

