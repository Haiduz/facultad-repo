#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);

typedef struct _BHeap {
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
} *BHeap;

void intercambiar(void **arr, int i, int j) {
    void *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int bheap_es_vacio(BHeap heap){
    return heap == NULL ||heap->ultimo == -1;
}

BHeap bheap_flotar(BHeap heap, int indice){
    if(bheap_es_vacio(heap) || indice == 0)return heap;
    // flota el nodo numero indice con su padre
    int c = heap->comp(heap->arr[indice], heap->arr[indice/2]);
    if(c<0){
        //menor que su padre no hace nada
        return heap;
    }
    // si pasamos el if el indice es mayor o igual a su padre
    intercambiar(heap->arr, indice, indice/2);
    // hace recu el padre del indice con su abuelo
    return bheap_flotar(heap, indice/2);
}

BHeap bheap_hundir(BHeap heap, int indice) {
    // Caso base: si el heap está vacío o el índice es inválido
    if (bheap_es_vacio(heap) || indice > heap ->ultimo) return heap;
    
    int izquierdo = 2 * indice + 1; // pq el primero es cero
    int derecho = 2 * indice + 2;
    int mayor = indice;

    // Verificar hijo izquierdo
    if (izquierdo <= heap->ultimo && 
        heap->comp(heap->arr[izquierdo], heap->arr[mayor]) > 0) {
        mayor = izquierdo;
    }

    // Verificar hijo derecho
    if (derecho <= heap->ultimo && 
        heap->comp(heap->arr[derecho], heap->arr[mayor]) > 0) {
        mayor = derecho;
    }

    // Si encontramos un hijo mayor, intercambiamos y continuamos hundiendo
    if (mayor != indice) {
        intercambiar(heap->arr, indice, mayor);
        return bheap_hundir(heap, mayor);
    }

    return heap;
}

BHeap crear(int capacidad, FuncionComparadora cmp){
    BHeap nuevo = malloc(sizeof(struct _BHeap));
    nuevo->arr= malloc(sizeof(void*)*capacidad);
    nuevo->capacidad= capacidad;
    nuevo->comp= cmp;
    nuevo->ultimo=-1;
    return nuevo;
}

void bheap_destruir(BHeap heap, FuncionDestructora destruir){
    if(heap == NULL) return;
    for(int i=0; i<= heap->ultimo; i++) destruir(heap->arr[i]);
    free(heap->arr);
    free(heap);
    return;
}

BHeap bheap_insertar(BHeap heap, void* dato) {
    if (!heap) return NULL;
    
    // Verificar capacidad y redimensionar si es necesario
    if (heap->ultimo >= heap->capacidad - 1) { // ultimo mas grande que la capacidad
        int nueva_capacidad = heap->capacidad * 2;
        void** nuevo_arr = realloc(heap->arr, sizeof(void*) * nueva_capacidad);
        heap->arr = nuevo_arr;
        heap->capacidad = nueva_capacidad;
    }
    
    // Insertar el nuevo elemento
    heap->ultimo++;
    heap->arr[heap->ultimo] = dato;
    
    // Flotar el elemento recién insertado
    return bheap_flotar(heap, heap->ultimo);
}

BHeap bheap_eliminar(BHeap heap, FuncionDestructora destruir){
    if(bheap_es_vacio(heap)) return heap;
    
    // Destruir el elemento de la raíz
    destruir(heap->arr[0]);
    
    // Mover el último elemento a la raíz
    heap->arr[0] = heap->arr[heap->ultimo];
    heap->ultimo--;
    
    // Hundir la nueva raíz
    return bheap_hundir(heap, 0);
}

// Funciones auxiliares para pruebas

int comparar_enteros(void* a, void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;  // Para max-heap
}

void destruir_entero(void* dato) {
    free(dato);
}

void* copiar_entero(void* dato) {
    int* nuevo = malloc(sizeof(int));
    *nuevo = *(int*)dato;
    return nuevo;
}

void imprimir_heap(BHeap heap) {
    if (bheap_es_vacio(heap)) {
        printf("Heap vacío\n");
        return;
    }
    
    printf("Heap (capacidad: %d, tamaño: %d): [", 
           heap->capacidad, heap->ultimo + 1);
    for (int i = 0; i <= heap->ultimo; i++) {
        printf("%d", *(int*)heap->arr[i]);
        if (i < heap->ultimo) printf(", ");
    }
    printf("]\n");
}

void prueba_operaciones_basicas() {
    printf("\n=== Prueba Operaciones Básicas ===\n");
    BHeap heap = crear(5, comparar_enteros);
    
    // Insertar elementos
    for (int i = 1; i <= 5; i++) {
        int* num = malloc(sizeof(int));
        *num = i;
        printf("Insertando %d...\n", *num);
        heap = bheap_insertar(heap, num);
        imprimir_heap(heap);
    }
    
    // Eliminar elementos
    while (!bheap_es_vacio(heap)) {
        int* max = heap->arr[0];
        printf("Eliminando máximo: %d\n", *max);
        heap = bheap_eliminar(heap, destruir_entero);
        imprimir_heap(heap);
    }
    
    bheap_destruir(heap, destruir_entero);
}

void prueba_redimension() {
    printf("\n=== Prueba Redimensión Automática ===\n");
    BHeap heap = crear(2, comparar_enteros);
    
    for (int i = 1; i <= 10; i++) {
        int* num = malloc(sizeof(int));
        *num = i * 10;
        printf("Insertando %d (Capacidad: %d)...\n", *num, heap->capacidad);
        heap = bheap_insertar(heap, num);
    }
    imprimir_heap(heap);
    
    bheap_destruir(heap, destruir_entero);
}

void prueba_eliminacion_multiple() {
    printf("\n=== Prueba Eliminación Múltiple ===\n");
    BHeap heap = crear(10, comparar_enteros);
    int valores[] = {23, 10, 49, 5, 32, 17, 41, 8, 29, 14};
    
    // Insertar valores desordenados
    for (int i = 0; i < 10; i++) {
        int* num = malloc(sizeof(int));
        *num = valores[i];
        heap = bheap_insertar(heap, num);
    }
    printf("Heap inicial:\n");
    imprimir_heap(heap);
    
    // Eliminar los 3 mayores
    for (int i = 0; i < 3; i++) {
        int* max = heap->arr[0];
        printf("Eliminando: %d\n", *max);
        heap = bheap_eliminar(heap, destruir_entero);
    }
    printf("Heap después de eliminar 3 elementos:\n");
    imprimir_heap(heap);
    
    bheap_destruir(heap, destruir_entero);
}

void prueba_heap_vacio() {
    printf("\n=== Prueba Comportamiento con Heap Vacío ===\n");
    BHeap heap = crear(5, comparar_enteros);
    
    printf("Intentando eliminar de heap vacío...\n");
    heap = bheap_eliminar(heap, destruir_entero);
    imprimir_heap(heap);
    
    bheap_destruir(heap, destruir_entero);
}

void prueba_valores_aleatorios() {
    printf("\n=== Prueba con Valores Aleatorios ===\n");
    BHeap heap = crear(1, comparar_enteros); // Pequeña capacidad inicial
    srand(time(NULL));
    
    // Insertar 15 números aleatorios
    for (int i = 0; i < 15; i++) {
        int* num = malloc(sizeof(int));
        *num = rand() % 100;
        printf("Insertando %d (Capacidad: %d)\n", *num, heap->capacidad);
        heap = bheap_insertar(heap, num);
    }
    imprimir_heap(heap);
    
    // Eliminar todos
    printf("Eliminando todos los elementos...\n");
    while (!bheap_es_vacio(heap)) {
        printf("Eliminado: %d\n", *(int*)heap->arr[0]);
        heap = bheap_eliminar(heap, destruir_entero);
    }
    
    bheap_destruir(heap, destruir_entero);
}

int main() {
    printf("=== INICIO DE PRUEBAS DEL BHEAP ===\n");
    
    prueba_operaciones_basicas();
    prueba_redimension();
    prueba_eliminacion_multiple();
    prueba_heap_vacio();
    prueba_valores_aleatorios();
    
    printf("\n=== TODAS LAS PRUEBAS COMPLETADAS ===\n");
    return 0;
}