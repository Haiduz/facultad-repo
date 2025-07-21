#ifndef __PILA_ARR__
#define __PILA_ARR__

typedef struct _Pila {
    int *arr;
    int ultimo;
    int capacidad;
    }pilita;

typedef pilita *Pila;

//crea e inicializa una nueva pila vacı́a con la capacidad dada.
Pila pila_crear(int); 

//libera la memoria requerida para la pila.
void pila_destruir(Pila); 

//retorna 1 si la pila está vacı́a, y 0 en caso contrario.
int pila_es_vacia(Pila);

//retorna el elemento que se encuentre en el tope de la pila, pero sin
int pila_tope(Pila);

//inserta un elemento en el tope de la pila, en caso que la pila
//se encuentre llena, deberá aumentar al doble la capacidad del arreglo.
void pila_apilar(Pila, int); 

//elimina el elemento que se encuentra en el tope de la pila.
void pila_desapilar(Pila);

//imprime en orden los elementos de la pila.
void pila_imprimir(Pila);

#endif
