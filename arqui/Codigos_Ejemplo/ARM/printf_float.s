.data
f: .float   3.14
str: .asciz  "%f\n"

.text
.global main
main:
        push    {r7, lr}
        add     r7, sp, #0
        ldr r3, =f
        vldr.32 s15, [r3]
        vcvt.f64.f32    d1, s15
        vmov    r2, r3, d1
        ldr     r0, =str
        bl      printf
        mov     r0, #0
        pop     {r7, pc}
        bx lr

