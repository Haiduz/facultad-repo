#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void handler(int s){
    switch (s)
    {
    case SIGQUIT:
        printf("ingresaste CTRL + / \n");
        break;
        
    case SIGINT:
        printf("ingresaste CTRL + c, restaurando a default \n");
        signal(SIGINT,SIG_DFL);
        break;
    }
}

int main(){
    signal(SIGQUIT,handler);
    signal(SIGINT,handler);
    while(1);
    return 0;
}