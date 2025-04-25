#include "src/dlist.h"
#include <stdio.h>

int main(){
    DList lista1 = dlist_crear();
    DList lista2 = dlist_crear();

    lista2 = dlist_agregar_inicio(lista2, 3);
    lista2 = dlist_agregar_inicio(lista2, 2);
    lista2 = dlist_agregar_inicio(lista2, 1);
    lista2 = dlist_agregar_final(lista2, 4);

    lista1 = dlist_agregar_inicio(lista1, 3);
    lista1 = dlist_agregar_inicio(lista1, 2);
    lista1 = dlist_agregar_inicio(lista1, 1);
    lista1 = dlist_agregar_final(lista1, 4);  
    printf("Lista1:");
    dlist_recorrer(lista1, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);
    puts("");
    printf("Lista2:");
    dlist_recorrer(lista2, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);
    puts("");

    dlist_concatenar(&lista1, lista2);
    
    printf("La longitud de la lista es %d \n", dlist_longitud(lista1));
    puts("");

    dlist_recorrer(lista1, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);
    puts("");

    dlist_destruir(lista1);
}