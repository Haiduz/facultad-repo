#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

// funciones triviales

int dlist_vaciayn(DList lista){
    return lista.primero == NULL;
} 

// crea nodo
DList dlist_crear(){
    DList lista = { NULL, NULL};
    // equivalente a 
    lista.primero = NULL;
    lista.ultimo = NULL;
    return lista;
}

// destruye la lista
void dlist_destruir(DList lista) {
    DNodo* nodo = lista.primero;
    while (nodo != NULL) {
        DNodo* temp = nodo;
        nodo = nodo->sig;
        free(temp); // Liberar cada nodo
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
    printf("%d ", a);
}

// agrega nodo al inico
DList dlist_agregar_inicio(DList lista, int dato) {
    DNodo* nuevonodo = malloc(sizeof(DNodo));
    nuevonodo->ant = NULL;
    nuevonodo->sig = lista.primero;
    nuevonodo->dato = dato;

    if(lista.primero == NULL) {
        lista.primero = lista.ultimo = nuevonodo;
    } else {
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

DList dlist_insertar(DList lista, int dato, int posicion){
    if(dlist_vaciayn(lista) || posicion == 1){
        lista = dlist_agregar_inicio(lista, dato);
        return lista;
    }else if(posicion >= dlist_longitud(lista)){
        lista = dlist_agregar_final(lista, dato);
        return lista;
    }

    DNodo* nuevonodo = malloc(sizeof(DNodo));
    DNodo* actual =  actual = lista.primero;
    nuevonodo->dato = dato;

    for(int i = 0 ; i < posicion-1 ; i++ , actual = actual->sig);
    
    nuevonodo->sig = actual->sig;
    nuevonodo->ant = actual;
    actual->sig->ant = nuevonodo;
    actual->sig = nuevonodo;
    
    return lista;
}

DList dlist_eliminar(DList lista, int posicion){
    if(dlist_vaciayn(lista)){
        return lista;
    }

    DNodo* actual = lista.primero;
    if(posicion == 1){
        //tengo que eliminar primer nodo
        lista.primero = actual->sig;
        lista.primero->ant = NULL;
        free(actual);
        return lista;
    }

    int longitud = dlist_longitud(lista);
    if(posicion >= longitud){
        // tengo que eliminar ultimo nodo
        actual = lista.ultimo;
        lista.ultimo = actual->ant;
        lista.ultimo->sig = NULL;
        free(actual);
        return lista;
    }
    for(int contador = 0; contador <posicion - 1; contador++, actual = actual->sig);
    actual->sig->ant = actual->ant;
    actual->ant->sig = actual->sig;
    free(actual);   
    return lista;
}

// verifica si un elemento esta en la lista
int dlist_contiene(DList lista, int dato) {
    DNodo* actual = lista.primero;
    
    while (actual != NULL) {
        if (actual->dato == dato) {
            return 1; // Verdadero
        }
        actual = actual->sig;
    }
    
    return 0; // Falso
}

// funcion para obtener el indice de un elemento
int dlist_indice(DList lista, int dato) {
    DNodo* actual = lista.primero;
    int indice = 0;
    
    while (actual != NULL) {
        if (actual->dato == dato) {
            return indice;
        }
        actual = actual->sig;
        indice++;
    }
    
    return -1; // No encontrado
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