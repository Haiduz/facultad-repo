#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

/*
    #include <signal.h>

struct sigaction {
    void     (*sa_handler)(int);   // Manejador o SIG_IGN/SIG_DFL
    void     (*sa_sigaction)(int, siginfo_t *, void *); // Manejador avanzado
    sigset_t   sa_mask;            // Señales a bloquear durante el handler
    int        sa_flags;           // Opciones de comportamiento
    void     (*sa_restorer)(void); // Obsoleto, no usar
};

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
*/

int main(){
    pid_t pid = getpid();
    printf("%d\n",pid);
    raise(SIGSTOP); // ya por defecto para la ejecucion sin necesidad de handler
    printf("Tocaste fg arranco de vuelta\n");    
    
    return 0;
}