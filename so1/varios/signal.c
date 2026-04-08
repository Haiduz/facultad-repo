#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


void handler(int s){
    char* str = "Me llego una señal que el wachin de mi hijo termino\n";  
    write(STDOUT_FILENO, str, strlen(str));
}

int main(){
    signal(SIGCHLD,handler); // señal que se emite cuando termina el hijo
    pid_t pid = fork();
    if(pid == 0){
        printf("soy el hijo mas wachin\n");
        sleep(2);
        exit(0);
    }
    else{
        sleep(7);
        printf("soy el papa la idea es esperar al wachin de mi hijo pero sin el wait");
    }
    
    exit(0);
    return 0;
}