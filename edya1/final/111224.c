#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE 100

typedef char* CasillaHash;

typedef struct TablaHash
{
    CasillaHash* tabla[SIZE];
    int capacidad;
}TablaHash;

int hash(char* palabra){
    int hash = 0;
    for(int i=0; palabra[i] != '\0'; i++) hash += palabra[i];
    return hash;
}



int main(){
    int a = hash("abc\0");
    printf(" %d \n", a);
    a = hash("cba\0");
    printf(" %d \n", a);
}