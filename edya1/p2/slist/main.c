#include "src/slist.h"
#include <stdio.h>

int main() {
    // Ejemplo básico de uso
    Slist lista = NULL;
    
    // Agregar elementos
    slist_agregar_final(&lista, 10);
    slist_agregar_final(&lista, 20);
    slist_agregar_inicio(&lista, 5);
    
    // Insertar en posición específica
    slist_insertar(&lista, 15, 2);
    
    // Mostrar longitud
    printf("Longitud de la lista: %d\n", slist_longitud(lista));
    
    // Verificar contenido
    if(slist_contiene(&lista, 20)) {
        printf("El 20 está en la lista\n");
    }
    
    // Obtener índice
    printf("Índice del 15: %d\n", slist_indice(&lista, 15));
    
    // Limpiar memoria
    slist_destruir(&lista);
    
    return 0;
}