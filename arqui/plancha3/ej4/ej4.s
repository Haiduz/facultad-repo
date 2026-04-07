.text
.global main
main:
    movq $-1, %rax 
    movb $0, %al 
    movw $0, %ax  
    movl $0, %eax
    ret
# todo sucede dentro del mismo registro entonces se va pisando lso valores indicados
# 1- set en 1 de todo el registro rax (por lo tanto todos sus subregistros)
# 2- set en 0 de los 8 lsb (subregistro %al)
# 3- set en 0 de los 16 lsb (subregistro %ax)
# 4- En teoria deberia de setearse los 16 lsb en cero, pero por algun motivo se extiende a 
# los 64 bits de rax, porque se extiende a los bits superiores? preguntar

# La carga de un valor en un subregistro de 32 bits establece los 32 bits superiores en 0
# independientemente del valor anterior
# En esta caso el seteo de eax en 0, setea los 32 bits superiores de rax en 0

