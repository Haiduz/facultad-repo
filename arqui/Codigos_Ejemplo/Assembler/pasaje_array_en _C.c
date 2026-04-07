/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
int A[]={1,2,3,4,5};
int suma(int A[], int B[]);
#include <stdio.h>

int main()
{
    int B[]={1,2,3,4,5};
    
    printf("%p %d %p %d\n",&A, A[4], &B, B[4]);
    
    int r0=suma(A,B);
    return r0;
}

int suma(int A[], int B[]){
    return A[2]+B[3];
}

