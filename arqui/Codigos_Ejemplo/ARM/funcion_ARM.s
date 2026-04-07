.text
.global funcion
funcion:
        push {r7,lr}
        vmul.f32 s2, s0, s1     @ s2=s0*s1=3.5
        mov r0, #10             @ r0=10
        vmov.f32 s0, r0         @ s0=10.0
        vcvt.f32.s32 s3, s0     @ s3=10.0
        vadd.f32 s4, s3, s2     @ s4=s2+s3=13.5
        vmov.f32  s0, s4        @ Copia del registro s4 al registro s0
        pop {r7,lr}
        bx    lr                 

