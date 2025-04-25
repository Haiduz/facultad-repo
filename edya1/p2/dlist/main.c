#include "src/dlist.h"
#include <stdio.h>

int main(){
    // 1. Crear una lista vacía
    DList lista = dlist_crear();
    printf("Lista creada. ¿Está vacía? %s\n", dlist_vaciayn(lista) ? "Sí" : "No");
    DList lista2 = dlist_crear();
    
    // 2. Agregar elementos al inicio y al final
    lista = dlist_agregar_inicio(lista, 10);
    lista = dlist_agregar_final(lista, 20);
    lista = dlist_agregar_inicio(lista, 5);
    
    lista2 = dlist_agregar_final(lista2, 100);
    lista2 = dlist_agregar_final(lista2, 200);
    lista2 = dlist_agregar_inicio(lista2, 10);
    
    printf("\nLista después de agregar 5, 10, 20:\n");
    dlist_recorrer(lista, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);

    printf("\nLista2 después de agregar 100, 200, 10:\n");
    dlist_recorrer(lista, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);

    // 3. Insertar en posición arbitraria
    lista = dlist_insertar(lista, 15, 2);
    lista = dlist_insertar(lista, 25, 4);
    printf("\nLista después de insertar 15 en pos 2 y 25 en pos 4:\n");
    dlist_recorrer(lista, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);

    // 4. Eliminar elementos
    lista = dlist_eliminar(lista, 1); // Eliminar segundo elemento (10)
    printf("\nLista después de eliminar posición 1:\n");
    dlist_recorrer(lista, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);

    // 5. Verificar contenido
    int buscar = 20;
    printf("\n¿La lista contiene %d? %s\n", buscar, dlist_contiene(lista, buscar) ? "Sí" : "No");
    printf("Índice de %d: %d\n", buscar, dlist_indice(lista, buscar));

    // 6. Recorrido hacia atrás
    printf("\nRecorrido hacia atrás:\n");
    dlist_recorrer(lista, imprimir_int, DLIST_RECORRIDO_HACIA_ATRAS);

    // 7. Probar longitud
    printf("\n\nLongitud de la lista: %d\n", dlist_longitud(lista));
    
    // 8. intersecar listas
    DList inter1 = dlist_intersecar(lista, lista2);
    printf("\nLista después de intersecar [10, 20, 5] y [100, 200, 10]:\n");
    dlist_recorrer(inter1, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE); 

    // 9. Concatenar listas 
    lista = dlist_concatenar(lista, lista2);
    printf("\nLista después de concatenar con [100, 200, 10]:\n");
    dlist_recorrer(lista, imprimir_int, DLIST_RECORRIDO_HACIA_ADELANTE);

    // 10. Destruir la lista
    dlist_destruir(lista);
    dlist_destruir(inter1);

    printf("!!  %d  ¡¡", lista.primero->dato);
    printf("\nListas destruidas. ¿Está vacía la principal? %s\n", dlist_vaciayn(lista) ? "Sí" : "No");

    return 0;
}