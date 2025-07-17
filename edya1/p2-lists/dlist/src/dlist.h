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
typedef int (*FuncionComparadora)(int, int);
// funciones triviales
int dlist_vaciayn(DList lista);
DList dlist_crear();
void imprimir_int(int a);
int dlist_longitud(DList lista);
int dlist_contiene(DList lista, int dato);
int dlist_indice(DList lista, int dato);
void dlist_destruir(DList lista);
void dlist_recorrer(DList lista, FuncionVisitante funcion, DListOrdenDeRecorrido orden);

// funciones basica
DList dlist_agregar_inicio(DList lista, int dato);
DList dlist_agregar_final(DList lista, int dato);
DList dlist_insertar(DList lista, int dato, int posicion);
DList dlist_eliminar(DList lista, int posicion);
// funciones avanzadas
DList dlist_concatenar(DList lista1, DList lista2);
DList dlist_intersecar(DList lista1, DList lista2);
DList dlist_intersecar_custom(DList lista1, DList lista2, FuncionComparadora cmp);
#endif