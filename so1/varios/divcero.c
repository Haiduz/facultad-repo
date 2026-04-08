#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


void handler(int s){
    char* str = "Me conto un pajaro que queres dividir por cero\n";  
    write(STDOUT_FILENO, str, strlen(str));
    printf(" el numero de la señal recibida es %d\n", s);
    exit(0);
}

int main(){
    /*Signal lo que hace es que determina como queres que actue una vez que se levanta
    si comento el signal hace la rutina normal de core dumped */
    signal(SIGFPE,handler);
    int a = 10;
    int b = 0;
    int c = a/b;
}