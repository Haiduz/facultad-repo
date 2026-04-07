#include <stdio.h>
int suma(int a, int b);

int main()
{
    int a=5, b=10;
    
    printf("La suma es: %d\n", suma(a,b));

    return 0;
}

int suma(int a, int b){
    return a+b; 
}

