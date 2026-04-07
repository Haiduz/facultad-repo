#include <stdio.h>

int puedo_suma_signed(short a, short b);

int main(){
	//printf("%d\n",puedo_suma_signed(0x7fff,1));
	//printf("%d\n",puedo_suma_signed(0x7ffe,1));

	if (puedo_suma_signed(0x7fff,1)){
		printf("Puedo sumar 0x7fff y 1\n");
	} else {
		printf("No puedo sumar 0x7fff y 1\n");
	}

	if (puedo_suma_signed(0x7ffe,1)){
		printf("Puedo sumar 0x7ffe y 1\n");
	} else {
		printf("No puedo sumar 0x7ffe y 1\n");
	}
}
