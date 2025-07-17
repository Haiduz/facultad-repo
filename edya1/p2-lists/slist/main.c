#include "src/slist.h"
#include <stdio.h>

int main() {

    Slist *lista;
    Slist *lista2;
    (*lista) = NULL;
    (*lista2) = NULL;
    // Agregar elementos
    slist_agregar_inicio(lista2, 3);
    slist_agregar_inicio(lista2, 2);
    slist_agregar_inicio(lista2, 1);
    slist_agregar_final(lista2, 4);
  
    slist_agregar_inicio(lista, 3);
    slist_agregar_inicio(lista, 2);
    slist_agregar_inicio(lista, 1);
    slist_agregar_final(lista, 4);
    
    // Insertar en posición específica
    slist_insertar(lista, 15, 2);
    
    // Mostrar longitud
    //printf("Longitud de la lista: %d\n", slist_longitud(*lista));
    
    // Verificar contenido
    if(slist_contiene(lista, 20)) {
        printf("El 20 está en la lista\n");
    }
    
    // Obtener índice
    printf("Índice del 15: %d\n", slist_indice(lista, 15));
    
    // imprime lista
    slist_recorrer((*lista), imprime_int);
    puts("");
    slist_recorrer((*lista2), imprime_int);
    puts("");

    //concatena y ordena
    slist_concatenar(lista, (*lista2));
    slist_recorrer((*lista), imprime_int);
    puts("");

    slist_ordenar(lista, mayor);
    slist_recorrer((*lista), imprime_int);
    puts("");


    // Limpiar memoria
    slist_destruir((*lista));
    //slist_destruir(lista2);
    
    return 0;
}