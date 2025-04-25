#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

// funciones triviales

// crea nodo
DList dlist_crear(){
    DList lista = { NULL, NULL};
    // equivalente a 
    lista.primero = NULL;
    lista.ultimo = NULL;
    return lista;
}

// destruye la lista
void dlist_destruir(DList lista){
    DNodo* nodo = lista.primero;
    while(lista.primero != NULL){
        nodo = lista.primero;
        lista.primero = lista.primero->sig; 
        free(nodo);
    }
}
 
// recorre fc visitante
void dlist_recorrer(DList lista, FuncionVisitante funcion, DListOrdenDeRecorrido orden){
    
    if(orden == DLIST_RECORRIDO_HACIA_ADELANTE){
        for(DNodo* nodo = lista.primero; nodo != NULL ; nodo = nodo->sig){
            funcion(nodo->dato);
        }

    }else{
        for(DNodo* nodo = lista.ultimo; nodo != NULL ; nodo = nodo->ant){
            funcion(nodo->dato);
        }

    }
}

// imprime entero
void imprimir_int(int a){
    printf("%d", a);
}

// agrega nodo al inico
DList dlist_agregar_inicio(DList lista, int dato){
    DNodo*  nuevonodo = malloc(sizeof(DNodo));
    nuevonodo->ant = NULL;
    nuevonodo->sig = lista.primero;
    nuevonodo->dato = dato;

    if(lista.primero == NULL){
        lista.primero = lista.ultimo = nuevonodo;
        lista.primero->ant = nuevonodo; 
    }else{
        lista.primero->ant = nuevonodo;
        lista.primero = nuevonodo;
    }

    return lista;
}

// agrega nodo al final
DList dlist_agregar_final(DList lista, int dato){
    DNodo*  nuevonodo = malloc(sizeof(DNodo));
    nuevonodo->sig = NULL;
    nuevonodo->ant = lista.ultimo;
    nuevonodo->dato = dato;
    
    
    if(lista.ultimo == NULL) { // Lista vacía
        lista.primero = lista.ultimo = nuevonodo;
    } else {
        lista.ultimo->sig = nuevonodo;
        lista.ultimo = nuevonodo;
    }

    return lista;
}

// Devuelve la cantidad de nodos en la lista.
int dlist_longitud(DList nodo) {
    int contador = 0;
    while(nodo.primero != NULL) {
        contador++;
        nodo.primero = nodo.primero->sig;
    }
    return contador;
}

//funcione avanzadas

// concatena dos listas
void dlist_concatenar(DList* lista1, DList lista2){
    if(lista1->primero == NULL) {
        *lista1 = lista2;
    } else if(lista2.primero != NULL) {
        lista1->ultimo->sig = lista2.primero;
        lista2.primero->ant = lista1->ultimo;
        lista1->ultimo = lista2.ultimo;
    }
}