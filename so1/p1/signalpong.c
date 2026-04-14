#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/*Luego del fork, el padre envia una senal SIGUSR1 al hijo y entra en un loop infinito. 
El hijo espera en un loop infinito. Ambos (padre e hijo) cuando reciven una senal SIGUSR1 
responden lo mismo. (el padre al hijo y el hijo al padre).
 ¿Que pasa si cambiamos los loops infinitos por pause()?. Usar las funciones
signal() y sigaction().*/

int xd = 0;

void handler(int sig){
    xd = 1;
    printf("Señal recibida loco levantaron la bandera\n");
    return;
}

void main(){
    signal(SIGUSR1, handler);
    __pid_t pid = fork();
    switch (pid)
    {
        case -1:
            printf(" El erro mas wachin\n");
            exit(0);
        break;
        
        case 0:
        // caso hijo
            printf("esperando la señal\n");
            while(!xd){}
        break;
        
        default:
            // caso padre
            kill(pid, SIGUSR1);
            wait(0);
            printf("hijo termino\n");
        break;
    }
    return;
}