.data
valFloat:  .word 0x3fe00000   @ 1.75
valFloat2: .word 0x40000000   @ 2.0

.text
.global main
main:
    ldr   r1, =valFloat     @ En r1 queda la dirección de valFloat
    vldr  s0, [r1]          @ En s0 queda el valor 1.75
    
    ldr   r1, =valFloat2    @ En r1 queda la dirección de valFloat2
    vldr  s1, [r1]          @ En s1 queda el valor 2.0
    
    vmul.f32 s2, s0, s1     @ s2=s0*s1=3.5
    mov r0, #10             @ r0=10
    vmov.f32 s0, r0         @ s0=10.0	
    vcvt.f32.s32 s3, s0     @ s3=10.0	
    vadd.f32 s4, s3, s2     @ s4=s2+s3=13.5
    
    vcvt.s32.f32 s0, s4     @ Conversión de punto flotante a entero (s0=13)
    vmov  r0, s0            @ Copia del registro s0 al registro r0 (r0=13)
    
    bx    lr                @ Retorna r0=13