#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>

void loop(char* buff){
    if(buff == NULL)return;
    char* args[64]; 
    int i = 0;
    args[i] = strtok(buff, " \n");
    while( args[i] != NULL){
        i++;
        args[i] = strtok(NULL, " \n");
    }
    for(int j=0;j<i; j++)printf("%s\n", args[j]);
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        printf(" El error mas wachin de la historia\n");
        exit(0);
        break;
    case 0: 
    // caso hijo
        execvp(args[0], args);
        break;
    default:
    // caso padre, toca esperar al hijo
        wait(0);
        break;
    }
}

void main(){
    char buff[100];
    printf(" Presione CTRL + C para terminar\n");
    while(1)
    {
        printf("$ ");
        fgets(buff, 100, stdin);
        loop(buff);
    }
    
}