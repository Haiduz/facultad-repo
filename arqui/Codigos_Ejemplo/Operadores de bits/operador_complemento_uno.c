#include<stdio.h>
int main(){
        int x=0xdeadbeef;
        x=x&~0xff;
        printf("0x%x\n",x);
        return 0;
}

