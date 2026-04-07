.data
place: .word -1

.text
.global main
main:
        LDR     r3, =0xff0
	   LDR     r3, =0xffffffff
        LDR     r1, =0xffff
        LDR     r2, =place
        bx      lr
