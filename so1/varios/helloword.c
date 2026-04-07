#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("Hello word!!\n");
    printf(" Soy hello word mi PID es %d\n", getpid());
    return 0; 
}