#ifndef __PILASGLIST__
#define __PILASGLIST__
#include "../../p2/glist/glist.h"

typedef GList Pila;

//crea e inicializa una nueva pila con el valor ingresado
Pila pila_crear(int); 

//libera la memoria requerida para la pila.
void pila_destruir(Pila); 

//retorna 1 si la pila está vacı́a, y 0 en caso contrario.
int pila_esvacia(Pila);

//retorna el elemento que se encuentre en el tope de la pila, pero sin
int pila_tope(Pila);

//inserta un elemento en el tope de la pila, en caso que la pila
//se encuentre llena, deberá aumentar al doble la capacidad del arreglo.
Pila pila_apilar(Pila, int); 

//elimina el elemento que se encuentra en el tope de la pila.
Pila pila_desapilar(Pila);

//imprime en orden los elementos de la pila.
void pila_imprimir(Pila);

// aux

void int_imprimir(void*);
void* int_copia(void*);

//3. Escriba una función que utilice una pila para revertir 
//el orden de una lista simplemente enlazada.

#endif
