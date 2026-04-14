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
con exec, el padre solamente espera q el hijo termino

En el ejercicio pide que redirija la salida al un archivo .txt
para hacer eso uso dup2 que redirige la salida del STDOUT_FILENO
al archivo .txt. Basicamente ademas de dirigir la salida y escribir en 
consola tambien lo hace en el fd de out.txt

open usa writeonly O_WRONLY y O_CREAT. dos bandera que permite escribir y modificar/crear un archivo en caso de que no este creado 

La ultima modificacion es hacer que la minishell acepte varios comandos
de la forma c1 | c2 | ... | cn donde la salida del comando anterior sea la entrada del comando siguiente. Para esto usamos int pipe(int pipe(2))

Luego de parsear todo, esta vez en arreglos bidimensionales. Para hacer esta pipeline seguimos la siguiente logica:

El parser nos determina cuantos comandos hay, entonces ya sabemos cuantos procesos distintos vamos a tener que hacer. 

La complejidad del ejercicio es poder conectar bien las pipes y entender como escribir y ejecutar comandos hijos redireccionando la salida.

Yo opte por un enfoque usando dos pipes. La pipe al anterior proceso prev_pipe y al siguiente next_pipe. Donde, si no soy el primer proceso, leo la prev_pipe. Y si no soy el ultimo proceso escribo en la next_pipe.

El kernel automaticamente conecta lo leido en STDIN_FILENO y lo conecta con el comando a ejecutar en 
execvp(cmd_args[i][0], cmd_args[i]) 
No comprendo bien porque pero lo toma como argumento (PREGUNTAR)

RTA: lo que sucede es que STDIN_FILENO es la entrada estandar, entonces toma como "escrito en consola" a lo leido por la pipe, que resulta los parametros de la funcion a ejecutar, esto sucede por defecto. Mas aun funciones como sort esperan parametros para ordenar, entonces con mas razon tiene sentido que se escriba despues de los comandos a ejecutar

OBS: Al hacer dup2 y redirigir tanto la salida como entrada estandar por la pipe, al ejecutar la instruccion exec. Una caracteristica de la misma es que mantiene los file descrpitors, entonces aunque se reemplace el marco en el que esta, el programa "RECUERDA" a que file descriptors tiene que escribir su salida. (PREGUNTAR)

RTA: SI, si cambio los files descriptors y despues hago un exec estos se mantiene excepto que el programa a ejecutar puntualmente vuelva a cambiarlos 

Notar que todos los procesos hijos "mueren" dentro del for, es decir, dentro de cada iteracion del for se hace un fork() donde:

1) El hijo setea las pipes y ejecuta un comando y "muere"

2) El padre actualiza la pipes (next pipe => prev pipe) pues este proceso se seguira ejectando. No "muere" dentro del for, sino que pasa a la siguiente iteracion y crea un nuevo hijo. 

Desde cierta persecptiva el programa tiene un unico proceso "PADRE" y tantos proceso "HERMANOS" como comandos haya. Cada hermano nunca sale del for pues por el exec cambia su marco