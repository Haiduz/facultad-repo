#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Hello word\n");
    int ad = 200, bd=300, cd = 500, dd=400,sd;
    long int ald = 300, bld = 300, cld=500, dld=400,sld;
    sd= ad*bd*cd*dd;
    sld=ald*bld*cld*dld;
    printf("Res int %d\nRes long int %ld\n", sd, sld);
    char a =127;
    printf ( " %hhd %hhu \n " ,a , a ) ;
    a =++ a; // signed char va desde -128 a 127
    printf( " %hhd %hhu \n " ,a , a ) ; // lleva a a 128 que en signed queda fuera de rango 
    unsigned char b =128;
    printf ( " %hhd %hhu \n " ,b , b ) ;
    b =++ b ;
    printf ( " %hhd %hhu \n " ,b , b ) ;
    return 0;
}