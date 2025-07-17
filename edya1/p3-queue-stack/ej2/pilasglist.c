#include "../../p2/glist/glist.h"
#include "pilasglist.h"
#include <stdlib.h>
#include <stdio.h>

typedef int Pila_dato;
typedef GList Pila;

// crea un lugar fisico donde se guarda el dato a apilar
int* crea_int(int dato){
    int* info = malloc(sizeof(int));
    *info = (dato);
    return info;
}
void int_imprimir(void* dato){
    printf("%d ", *((int*)dato));
}

void* int_copia(void* dato) {
    int* original = (int*)dato;
    int* copia = malloc(sizeof(int));
    *copia = *original;
    return copia;
}
//crea e inicializa una nueva con el valor ingresado
Pila pila_crear(int dato){
    // la pila resulta un puntero a una glist
    Pila p = NULL;
    p = pila_apilar(p,dato);
    p -> next = NULL;
    return p;
}

int pila_esvacia(Pila p){
    return (p == NULL);
}

void pila_destruir(Pila p){
    // el dato se liber pq usamos malloc
    if(!pila_esvacia(p))free(p->data);
    free(p);

}

//retorna el elemento que se encuentre en el tope de la pila, pero sin
int pila_tope(Pila p){
    if(pila_esvacia(p)) return 0;
    return *((int*)(p->data));
}

//inserta un elemento en el tope de la pila, en caso que la pila
//se encuentre llena, deberá aumentar al doble la capacidad del arreglo.
Pila pila_apilar(Pila p, int dato) {
    void* dato_ptr = crea_int(dato);
    p = glist_agregar_inicio(p, dato_ptr, (FuncionCopia)int_copia); 
    return p;
} 


//imprime en orden los elementos de la pila.
void pila_imprimir(Pila p){
    glist_recorrer(p, (FuncionVisitante)int_imprimir);
    return;
}

//elimina el elemento que se encuentra en el tope de la pila.
Pila pila_desapilar(Pila p){
    if(pila_esvacia(p))return p;
    p = glist_eliminar_header(p, free);
    return p;
}

