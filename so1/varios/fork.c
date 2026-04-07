#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>  

int main() {
    pid_t pid;
    char* args[] = {"/home/haiduz/Desktop/so1/helloword", NULL}; 
    
    printf("Soy el padre, mi PID es %d\n", getpid());  
    
    pid = fork();
    printf("    fork retorna %d\n", pid);
    switch (pid) {
        case -1:
            perror("Error en fork");  // perror da más información
            exit(1);
            break;
            
        case 0:  
            printf("Soy el hijo, mi PID es %d\n", getpid());
            printf("Voy a ejecutar helloworld\n");
            
            execvp(args[0], args);
            printf(" Esto no se deberia imprimir por el execvp");
            break;
            
        default:  // PROCESO PADRE
            wait(0);  // Espera a que cualquier hijo termine
            printf("Padre: Mi hijo terminó\n");
            break;
    }
    
    return 0;
}