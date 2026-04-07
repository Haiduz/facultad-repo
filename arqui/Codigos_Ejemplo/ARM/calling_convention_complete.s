int calculo(int a, int b, int c, int d, float e, double f, int g, int h){
    return a + b + c + d + g + h;
}

int main(){
    return calculo(1, 2, 3, 4, 5.0, 6.0, 7, 8);
}

calculo:
        push    {r7}
        sub     sp, sp, #36
        add     r7, sp, #0
        str     r0, [r7, #28]
        str     r1, [r7, #24]
        str     r2, [r7, #20]
        str     r3, [r7, #16]
        vstr.32 s0, [r7, #12]
        vstr.64 d1, [r7]
        ldr     r2, [r7, #28]
        ldr     r3, [r7, #24]
        add     r2, r2, r3
        ldr     r3, [r7, #20]
        add     r2, r2, r3
        ldr     r3, [r7, #16]
        add     r2, r2, r3
        ldr     r3, [r7, #40]
        add     r2, r2, r3
        ldr     r3, [r7, #44]
        add     r3, r3, r2
        mov     r0, r3
        adds    r7, r7, #36
        mov     sp, r7
        ldr     r7, [sp], #4
        bx      lr

.text
.global main
main:
        push    {r7, lr}
        sub     sp, sp, #8
        add     r7, sp, #8
        movs    r3, #8
        str     r3, [sp, #4]
        movs    r3, #7
        str     r3, [sp]
        vmov.f64        d1, #6.0e+0
        vmov.f32        s0, #5.0e+0
        movs    r3, #4
        movs    r2, #3
        movs    r1, #2
        movs    r0, #1
        bl      calculo
        mov     r3, r0
        mov     r0, r3
        mov     sp, r7
        pop     {r7, pc}