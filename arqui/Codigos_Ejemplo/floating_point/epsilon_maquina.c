#include <stdio.h>
int main(){
    float x = 1.0;
    double y = 1.0; 
    
    printf("Float: %ld bytes, Double: %ld bytes\n", sizeof(x), sizeof(y));
    
    int n = 0;
    
    while ((float)1.0 + (x * (float)0.5) > (float)1.0){
        ++n;
        x *= 0.5;
    }
    puts("-------------------------------------------------------");
    printf("Float: Epsilon de máquina en binario = 2^(-\%d)\n", n);
    printf("Float: Epsilon de máquina en decimal = \%G\n", x);
    puts("-------------------------------------------------------");
    
    n = 0;
    while (1.0 + (y * 0.5) > 1.0){
        ++n;
        y *= 0.5;
    }
    printf("Double: Epsilon de máquina en binario = 2^(-\%d)\n", n);
    printf("Double: Epsilon de máquina en decimal = \%G\n", y);
    
    
    return 0;
}