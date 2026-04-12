#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>

void loop(char* buff){
    if(buff == NULL)return;
    // PARSER PARSERSITO
    char* cmd[64]; 
    int cmd_idx = 0;

    cmd[cmd_idx] = strtok(buff, "|");
    while( cmd[cmd_idx] != NULL){
        cmd_idx++;
        cmd[cmd_idx] = strtok(NULL, "|");
    }


    char *cmd_args[64][64];

    for (int i = 0; i < cmd_idx; i++) {
        int j = 0;
        cmd_args[i][j] = strtok(cmd[i], " \n"); 

        while (cmd_args[i][j] != NULL) {
            j++;
            cmd_args[i][j] = strtok(NULL, " \n");
        }
    }
    // =============================================================

    int prev_pipe[2]; // el pipe 0 lectura pipe 1 escritura
    int next_pipe[2];

    for(int i = 0; i < cmd_idx; i++){
        // si no soy el ultimo proceso creo una pipe
        if(i<cmd_idx-1)pipe(next_pipe); 

        pid_t pid = fork();
        
        switch (pid){
            case -1:
                printf(" El error mas wachin de la historia\n");
                exit(0);
                break;
            case 0: 
            // caso hijo
                if(i>0){
                } // si no soy el primer comando -> leo la pipe del proc ant y cierro pipes antes de ejecutar
                    dup2(prev_pipe[0], STDIN_FILENO);
                    close(prev_pipe[1]);
                    close(prev_pipe[0]);
                if(i<cmd_idx-1){
                }// si no soy el ultimo comando -> escribo en la prox pipe y cierro pipes antes de ejecutar
                    dup2(next_pipe[1],STDOUT_FILENO);
                    close(next_pipe[1]);
                    close(next_pipe[0]);
                execvp(cmd_args[i][0], cmd_args[i]);
            default:
            // caso padre, cierro las pipes que ya no se usan
                if (i > 0) { // si no soy el primero cierro las pipes anteriores
                    close(prev_pipe[0]);
                    close(prev_pipe[1]);
                }               

                if (i < cmd_idx - 1) { // si hay siguientes actualizo los pipes
                    prev_pipe[0] = next_pipe[0];
                    prev_pipe[1] = next_pipe[1];
                }
                break;
        }

        
    }
    for(int i = 0; i<cmd_idx ; i++)wait(NULL);
    return;
      
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