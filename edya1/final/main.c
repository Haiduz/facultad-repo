#include "header.h"
#include <stdio.h>
#include <string.h>

/* Funciones auxiliares para enteros */
void* copiar_entero(void* dato) {
    int* nuevo = malloc(sizeof(int));
    if (nuevo) *nuevo = *(int*)dato;
    return nuevo;
}

int comparar_enteros(void* dato1, void* dato2) {
    return *(int*)dato1 - *(int*)dato2;
}

void destruir_entero(void* dato) {
    free(dato);
}

void imprimir_entero(void* dato) {
    printf("%d ", *(int*)dato);
}

/* Función principal */
int main() {
    printf("=== PRUEBA DE LISTA DOBLEMENTE ENLAZADA ===\n");
    Dlist lista = dlist_create(copiar_entero, comparar_enteros, destruir_entero, imprimir_entero);
    
    int valores_lista[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        lista = dlist_insert(lista, &valores_lista[i]);
    }
    printf("Lista después de inserciones: ");
    dlist_imprimir(lista); // Necesitarías implementar esta función
    lista=dlist_destroy(lista);
    if(dlist_empty(lista)) printf("\n Lista destruida correctamente \n");
    printf("\n\n=== PRUEBA DE PILA (STACK) ===\n");
    Stack pila = stack_create(copiar_entero, comparar_enteros, destruir_entero, imprimir_entero);
    
    int valores_pila[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        pila = push(pila, &valores_pila[i]);
    }
    
    printf("Elemento superior: ");
    imprimir_entero(top(pila));
    printf("\n");
    
    printf("Pop: ");
    while (!stack_empty(pila)) {
        imprimir_entero(top(pila));
        pila = pop(pila);
    }
    printf("\n");
    
    printf("\n=== PRUEBA DE COLA (QUEUE) ===\n");
    Queue cola = queue_create(copiar_entero, comparar_enteros, destruir_entero, imprimir_entero);
    
    int valores_cola[] = {100, 200, 300};
    for (int i = 0; i < 3; i++) {
        cola = enqueue(cola, &valores_cola[i]);
    }
    
    printf("Dequeue: ");
    while (!queue_empty(cola)) {
        imprimir_entero(front(cola));
        cola = dequeue(cola);
    }
    printf("\n");
    
    printf("\n=== PRUEBA DE ÁRBOL BINARIO DE BÚSQUEDA ===\n");
    BTree arbol = btree_create(copiar_entero, comparar_enteros, destruir_entero, imprimir_entero);
    
    int valores_arbol[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        arbol = bst_insert(arbol, &valores_arbol[i]);
    }
    int nodos = btree_nnodes(arbol);
    printf(" El arbol tiene %d nodos \n", nodos);
    
    printf("Recorrido IN_ORDER: ");
    btree_traverse(arbol, IN_ORDER);
    printf("\n");
    
    printf("Recorrido PRE_ORDER: ");
    btree_traverse(arbol, PRE_ORDER);
    printf("\n");
    
    printf("Recorrido POST_ORDER: ");
    btree_traverse(arbol, POST_ORDER);
    printf("\n");
    
    printf("Recorrido BFS (por niveles): ");
    btree_traverse(arbol, BFS);
    printf("\n");
    
    int valor_eliminar = 50;
    if(btree_find(arbol, &valor_eliminar))printf("El numero 50 se encuentra en el arbol\n");
    arbol = bst_delete(arbol, &valor_eliminar);
    if(!btree_find(arbol, &valor_eliminar))printf("El numero 50 NO se encuentra en el arbol\n");
    printf("\nÁrbol después de eliminar %d (IN_ORDER): ", valor_eliminar);
    btree_traverse(arbol, IN_ORDER);
    printf("\n");
    arbol = btree_destroy(arbol);
    if(btree_empty(arbol)) printf(" \n Arbol destuido correctamente \n");
    return 0;
}