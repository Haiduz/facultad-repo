#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Voy a correr hello word\n");

    char* args[] = {"./helloword",NULL};
    execvp(args[0], args);
    // ver como estas lineas de abajo no se ejecutan, pues el proceso actual
    // es reemplazado por la ejecucion de hello word
    printf("mamapinga");

    return 0; 
}
