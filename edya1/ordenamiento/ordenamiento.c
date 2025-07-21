#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void merge(int* a, int inicio, int medio, int fin){
    // es iterativo no hay caso base
    int nL =  medio-inicio+1; // longitud del primer subarreglo
    int nR = fin - medio;   
    int* L = malloc(sizeof(int)* nL);
    int* R = malloc(sizeof(int)* nR);
    for(int i=0; i< nL; i++)L[i] = a[inicio + i];
    for(int j=0; j< nR; j++)R[j] = a[medio+j+1];
    int  i=0, j=0, k = inicio;
    while( i< nL && j < nR){
        if(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }
    // si sale del while es porque alguno de los dos se fue de rango o ambos
    while(i< nL){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j< nR){
        a[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
void mergesort_R(int* a, int inicio, int fin){
    // caso base cuando el arreglo tiene uno o cero elementos
    if( inicio >= fin) return;
    // tiene mas de un elemento el arreglo
    int medio = (inicio + fin)/2;
    mergesort_R(a, inicio, medio);
    // OBS: la mitad del arreglo es el ultimo del primer subarreglo
    mergesort_R(a, medio+1, fin);

    merge(a, inicio, medio, fin);
    return;
}

void mergesort(int *a, int len){
    mergesort_R(a, 0, len-1);
}

void swap(int* a, int i, int j){
    int temp= a[i];
    a[i]= a[j];
    a[j] = temp;
}

void insertion_sort(int* a, int n){
    for(int i = 1; i<n; i++){
        for(int j=i; j>0 && a[j]<a[j-1]; j--){
                swap(a, j, j-1);
        }
    }
}

void selection_sort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;  
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j; 
            }
        }
        
        swap(a, min_idx, i);
    }
}

// Función para dividir el array y obtener el índice del pivote
int partition(int* arr, int low, int high) {
    int pivot = arr[high];  // Elegimos el último elemento como pivote
    int i = low - 1;        // Índice del menor elemento
    //printf("low es %d, high es %d", low, high);
    for (int j = low; j < high; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++;
            // evitamos error pues comienza con i == -1
            swap(arr,i, j);  // Intercambiamos arr[i] y arr[j]
        }
    }
    swap(arr,i + 1, high);   // Colocamos el pivote en su posición correcta
    return i + 1;                    // Retornamos el índice del pivote
}

// Función principal de Quicksort
void quicksort(int* arr, int low, int high) {
    if (low < high) {
        // Obtenemos el índice del pivote
        int pi = partition(arr, low, high);

        // Ordenamos recursivamente los subarrays antes y después del pivote
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Función para imprimir un arreglo
void imprimir_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Algoritmo de ordenamiento (Bubble Sort como ejemplo)
void ordenar_arreglo(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Intercambiar
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Búsqueda binaria (para arreglos ordenados)
int busqueda_binaria(int arr[], int n, int objetivo) {
    int izquierda = 0;
    int derecha = n - 1;
    
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        
        if (arr[medio] == objetivo) {
            return medio;
        }
        
        if (arr[medio] < objetivo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    
    return -1;
}

// Función para generar arreglo aleatorio
void generar_arreglo_aleatorio(int arr[], int n, int rango) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % rango;
    }
}

// Función para generar arreglo ordenado
void generar_arreglo_ordenado(int arr[], int n, int rango) {
    generar_arreglo_aleatorio(arr, n, rango);
    ordenar_arreglo(arr, n);
}

int main() {
    srand(time(NULL)); // Semilla para números aleatorios
    
    const int TAMANO = 10;
    const int RANGO = 100;
    int arreglo[TAMANO];
    
    /*int arreglo_ordenado[TAMANO];
    
    // Generar y mostrar arreglo aleatorio
    generar_arreglo_aleatorio(arreglo, TAMANO, RANGO);
    printf("Arreglo original (no ordenado):\n");
    imprimir_arreglo(arreglo, TAMANO);
    
    // Ordenar y mostrar
    ordenar_arreglo(arreglo, TAMANO);
    printf("\nArreglo ordenado:\n");
    imprimir_arreglo(arreglo, TAMANO);
    
    // Generar y mostrar arreglo ya ordenado
    generar_arreglo_ordenado(arreglo_ordenado, TAMANO, RANGO);
    printf("\nArreglo generado ya ordenado:\n");
    imprimir_arreglo(arreglo_ordenado, TAMANO);
    
    // Pruebas de búsqueda
    int objetivo;
    printf("\nIngrese un número a buscar (0-%d): ", RANGO-1);
    scanf("%d", &objetivo);
    
    // Búsqueda en arreglo original (ahora ordenado)
    printf("\nBúsqueda en arreglo ordenado:\n");
    int pos = busqueda_binaria(arreglo, TAMANO, objetivo);
    if (pos != -1) {
        printf("Encontrado en posición %d (búsqueda binaria)\n", pos);
    } else {
        printf("No encontrado (búsqueda binaria)\n");
    }
    
    // Búsqueda en arreglo no ordenado (necesitaríamos regenerarlo)
    generar_arreglo_aleatorio(arreglo, TAMANO, RANGO);
    printf("\nArreglo no ordenado regenerado:\n");
    imprimir_arreglo(arreglo, TAMANO);
    */

    // Generar y mostrar arreglo aleatorio
    generar_arreglo_aleatorio(arreglo, TAMANO, RANGO);
    printf("Arreglo original (no ordenado):\n");
    imprimir_arreglo(arreglo, TAMANO);
    // Ordenar y mostrar
    mergesort(arreglo, TAMANO);
    printf("\nArreglo ordenado con mergesort:\n");
    imprimir_arreglo(arreglo, TAMANO);

    // Generar y mostrar arreglo aleatorio
    generar_arreglo_aleatorio(arreglo, TAMANO, RANGO);
    printf("Arreglo original (no ordenado):\n");
    imprimir_arreglo(arreglo, TAMANO);
    // Ordenar y mostrar
    insertion_sort(arreglo, TAMANO);
    printf("\nArreglo ordenado con insertion:\n");
    imprimir_arreglo(arreglo, TAMANO);
        
    // Generar y mostrar arreglo aleatorio
    generar_arreglo_aleatorio(arreglo, TAMANO, RANGO);
    printf("Arreglo original (no ordenado):\n");
    imprimir_arreglo(arreglo, TAMANO);
    // Ordenar y mostrar
    selection_sort(arreglo, TAMANO);
    printf("\nArreglo ordenado con selection:\n");
    imprimir_arreglo(arreglo, TAMANO);

    // Generar y mostrar arreglo aleatorio
    generar_arreglo_aleatorio(arreglo, TAMANO, RANGO);
    printf("Arreglo original (no ordenado):\n");
    imprimir_arreglo(arreglo, TAMANO);
    // Ordenar y mostrar
    quicksort(arreglo, 0, TAMANO-1);
    printf("\nArreglo ordenado con qsort:\n");
    imprimir_arreglo(arreglo, TAMANO);

    return 0;
}
