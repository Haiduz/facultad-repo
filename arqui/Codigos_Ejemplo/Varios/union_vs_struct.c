#include <stdio.h>
union ficha{
   float salario;
   int legajo;
};

struct ficha1{
   float salario;
   int legajo;
};

int main() {
   union ficha j;    
   j.salario = 100000.0;

   // cuando se le asigna un valor a j.salario,
   // j.salario ya no contiene 100000
   j.legajo = 145;

   printf("salario = %.1f\n", j.salario);
   printf("Numero de legajo = %d\n", j.legajo);
   printf("Tamanio de la union %ld bytes\n",sizeof(j));
   
   struct ficha1 j1;
   j1.salario = 100000.0;
   j1.legajo = 145;

   printf("salario = %.1f\n", j1.salario);
   printf("Numero de legajo = %d\n", j1.legajo);
   printf("Tamanio de la estructura %ld bytes\n",sizeof(j1));
   return 0;
}
    
    