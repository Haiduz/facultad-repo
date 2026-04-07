#include <stdio.h>


char l=7;
short g=2;
int a=5, b=10;


int main()
{
    int c=2, d=3;
    printf("Suma: %d\n", a+b+c+d+g+l);
    printf(" Direccion de l: %p \n Direccion de g: %p \n Direccion de a: %p \n Direcci0n de b: %p\n Direcci0n de c: %p\n Direcci0n de d: %p\n",&l,&g,&a,&b,&c,&d);
    return 0;
}
