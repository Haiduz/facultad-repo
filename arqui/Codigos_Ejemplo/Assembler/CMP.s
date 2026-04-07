# Si op. destino > op. fuente
#       SF=0, ZF=0
# Si op. destino < op. fuente
#       SF=1, ZF=0
# Si op. destino == op. fuente
#       SF=0, ZF=1

.text
.global main
main:
        movb $15, %dl
        movb $10, %al
        cmpb %al, %dl
        ret