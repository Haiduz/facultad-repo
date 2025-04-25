#ifndef LISTA_H
#define LISTA_H

typedef struct _DNodo {
    int dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo;
    
typedef struct {
    DNodo* primero;
    DNodo* ultimo;
} DList;

typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;  

typedef void (*FuncionVisitante)(int);

// funciones triviales
DList dlist_crear();
void dlist_destruir(DList lista);
void dlist_recorrer(DList lista, FuncionVisitante funcion, DListOrdenDeRecorrido orden);
void imprimir_int(int a);
DList dlist_agregar_inicio(DList lista, int dato);
DList dlist_agregar_final(DList lista, int dato);
int dlist_longitud(DList lista);
// funciones avanzadas
void dlist_concatenar(DList* lista1, DList lista2);
#endif