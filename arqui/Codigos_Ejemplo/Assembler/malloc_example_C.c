#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p;
    p=malloc(4*sizeof(int));
    p[0]=0x11;
    p[1]=0x22;
    p[2]=0x33;
    p[3]=0x44;
    return 0;
}
