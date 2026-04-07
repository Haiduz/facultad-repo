#include <stdio.h>

int main(void)
{
    int a = -1;
    char b = -1;
    printf("a: %u %d %X %x, direccion: %p\n", a, a, a, a, &a);
    printf("b: %u %d %X %x, direccion: %p\n\n", b, b, b, b, &b);
    printf("b: %hhu %hhd %hhX %hhx\n", b, b, b, b);

    unsigned char ua = 128;
    char sa = -128; 
    printf("ua: %hhu sa: %hhu\n", ua, sa);
    printf("ua: %hhd sa: %hhd\n", ua, sa);
    ua += 1;
    sa += 1;
    printf("ua: %hhu sa: %hhu\n", ua, sa);
    printf("ua: %hhd sa: %hhd\n", ua, sa);
    return 0;
}

