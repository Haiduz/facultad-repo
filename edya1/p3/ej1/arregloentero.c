#include "arregloentero.h"
#include <stdlib.h>
#include <stdio.h>

//crea e inicializa una nueva pila vacı́a con la capacidad dada.
Pila pila_crear(int tamanio){
    Pila nuevapila = malloc(sizeof(pilita));
    nuevapila -> arr = (int*)malloc(sizeof(int)*tamanio);
    nuevapila -> ultimo = -1;
    nuevapila -> capacidad = tamanio;
    return nuevapila;
}

//libera la memoria requerida para la pila.
void pila_destruir(Pila pila){
    free(pila->arr);
    free(pila);
}

//retorna 1 si la pila está vacı́a, y 0 en caso contrario.
int pila_es_vacia(Pila pila){
    if(pila == NULL || pila->arr == NULL) return 1;
    return 0;
}

//retorna el elemento que se encuentre en el tope de la pila, pero sin
int pila_tope(Pila pila){
    //if(pila_es_vacia(pila)) return -1;
    return (pila->arr)[pila->ultimo];
}

//inserta un elemento en el tope de la pila, en caso que la pila
//se encuentre llena, deberá aumentar al doble la capacidad del arreglo.
void pila_apilar(Pila pila, int dato){
    if(pila->ultimo == pila->capacidad - 1){
        pila -> capacidad = pila -> capacidad * 2;
        pila -> arr = realloc(pila->arr, sizeof(int) * pila->capacidad);
    }
    pila -> ultimo++;
    (pila -> arr)[pila -> ultimo] = dato;
}

//elimina el elemento que se encuentra en el tope de la pila.
void pila_desapilar(Pila pila){
    if(pila_es_vacia(pila)) return;
    pila->ultimo--;
}

//imprime en orden los elementos de la pila.
void pila_imprimir(Pila pila){
    for(int i = 0; i <= pila -> ultimo; i++){
        printf("%d ", pila->arr[i]);
    }
}
