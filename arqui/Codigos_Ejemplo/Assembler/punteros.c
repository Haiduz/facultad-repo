#include<stdio.h>
int a[]={11, 22, 33, 44, 55};

int main()
{
    int b=a[0];
    int *p;
    p=&a[0];
    printf("%p\n",p);
    *p=99;
    printf("%d\n",b);
    b=*p;
    printf("%d\n",b);
    b=*(p+4);
    printf("%d\n",b);
    return 0;
}

