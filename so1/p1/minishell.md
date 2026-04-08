Ej. 7 (Mini Shell). Implemente una versi´on m´ınima de una shell. El programa deber´a esperar l´ıneas
por entrada est´andar, y al recibir una ejecutar el comando correspondiente, de la misma manera que lo
hace, por ejemplo, bash.
a) Implemente una versi´on b´asica que simplemente ejecuta el comando y espera que el mismo termine
antes de pedir otro. El comando puede especificarse por su path completo o solamente por su nombre
si se encuentra en alg´un directorio del $PATH (pista: ver execvp()). Ejemplo:
$ ls
Makefile shell.c shell

Mi idea es que el programa se divida en 6 etapas

Leer línea del usuario
Parsear
Crear proceso hijo con fork()
Ejecutar comando en el hijo con execvp()
Padre espera con wait()
Volver al paso 1

para leer las lineas nomas uso un buffer y la funcion 
getchar que es la mejor del mundo. 

Para parsear el truco esta en el strtok, la funcion esa 
hace todo, te separa el string original es substring, 
lleva un puntero interno, por eso luago al llamar la fc
con null sigue con el resutado anterior

luego preparo el arreglo de argumentos

por ultimo creo un proceso hijo y en el ejecuto los comandos
con exec, el padre solamente espera
