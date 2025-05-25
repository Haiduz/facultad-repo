#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

// Función auxiliar para imprimir un entero
void imprimir_int(int dato) {
    printf("%d ", dato);
}

int main() {
    printf("=== PRUEBAS DE ARBOL BINARIO ===\n\n");
    
    // Crear algunos árboles para pruebas
    BTree vacio = btree_crear();
    BTree hoja1 = btree_unir(1, btree_crear(), btree_crear());
    BTree hoja2 = btree_unir(2, btree_crear(), btree_crear());
    BTree hoja3 = btree_unir(3, btree_crear(), btree_crear());
    BTree arbol1 = btree_unir(4, hoja1, hoja2);
    BTree arbol2 = btree_unir(5, arbol1, hoja3);
    
    // Árbol más complejo
    BTree arbol = btree_unir(10, 
                    btree_unir(5, 
                        btree_unir(3, btree_crear(), btree_crear()),
                        btree_unir(7, btree_crear(), btree_crear())),
                    btree_unir(15, 
                        btree_unir(12, btree_crear(), btree_crear()),
                        btree_unir(20, btree_crear(), btree_crear())));
    
    // Prueba btree_empty
    printf("Prueba btree_empty:\n");
    printf("Arbol vacio: %d (esperado: 1)\n", btree_empty(vacio));
    printf("Arbol no vacio: %d (esperado: 0)\n\n", btree_empty(arbol1));
    
    // Prueba btree_nnodos
    printf("Prueba btree_nnodos:\n");
    printf("Nodos en arbol vacio: %d (esperado: 0)\n", btree_nnodos(vacio));
    printf("Nodos en arbol simple: %d (esperado: 3)\n", btree_nnodos(arbol1));
    printf("Nodos en arbol complejo: %d (esperado: 7)\n\n", btree_nnodos(arbol));
    
    // Prueba btree_buscar
    printf("Prueba btree_buscar:\n");
    printf("Buscar 5 en arbol vacio: %d (esperado: 0)\n", btree_buscar(vacio, 5));
    printf("Buscar 2 en arbol1: %d (esperado: 1)\n", btree_buscar(arbol1, 2));
    printf("Buscar 99 en arbol complejo: %d (esperado: 0)\n", btree_buscar(arbol, 99));
    printf("Buscar 12 en arbol complejo: %d (esperado: 1)\n\n", btree_buscar(arbol, 12));
    
    // Prueba btree_copia
    printf("Prueba btree_copia:\n");
    BTree copia = btree_copia(arbol);
    printf("Recorrido del arbol original (preorden): ");
    btree_recorrer(arbol, BTREE_RECORRIDO_PRE, imprimir_int);
    printf("\nRecorrido de la copia (preorden): ");
    btree_recorrer(copia, BTREE_RECORRIDO_PRE, imprimir_int);
    printf("\n\n");
    btree_destruir(copia);
    
    // Prueba btree_altura
    printf("Prueba btree_altura:\n");
    printf("Altura arbol vacio: %d (esperado: 0)\n", btree_altura(vacio));
    printf("Altura arbol simple: %d (esperado: 2)\n", btree_altura(arbol1));
    printf("Altura arbol complejo: %d (esperado: 3)\n\n", btree_altura(arbol));
    
    // Prueba btree_sumar
    printf("Prueba btree_sumar:\n");
    printf("Suma arbol vacio: %d (esperado: 0)\n", btree_sumar(vacio));
    printf("Suma arbol simple: %d (esperado: 7)\n", btree_sumar(arbol1));
    printf("Suma arbol complejo: %d (esperado: 72)\n\n", btree_sumar(arbol));
    
    // Prueba btree_nnodos_profundidad
    printf("Prueba btree_nnodos_profundidad:\n");
    printf("Nodos en profundidad 0: %d (esperado: 1)\n", btree_nnodos_profundidad(arbol, 0, 0));
    printf("Nodos en profundidad 1: %d (esperado: 2)\n", btree_nnodos_profundidad(arbol, 1, 0));
    printf("Nodos en profundidad 2: %d (esperado: 4)\n\n", btree_nnodos_profundidad(arbol, 2, 0));
    
    // Prueba btree_recorrer
    printf("Prueba btree_recorrer:\n");
    
    printf("Recorrido preorden: ");
    btree_recorrer(arbol, BTREE_RECORRIDO_PRE, imprimir_int);
    printf("\n");
    
    printf("Recorrido inorden: ");
    btree_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_int);
    printf("\n");
    
    printf("Recorrido postorden: ");
    btree_recorrer(arbol, BTREE_RECORRIDO_POST, imprimir_int);
    printf("\n");
    
    printf("Recorrido preorden iterativo: ");
    btree_recorrer(arbol, BTREE_RECORRIDO_PRE_ITE, imprimir_int);
    printf("\n\n");
    
    // Limpieza
    // Limpieza correcta:
    btree_destruir(arbol);
    btree_destruir(arbol2);  
    btree_destruir(vacio);  
    
    printf("=== TODAS LAS PRUEBAS COMPLETADAS ===\n");
    
    return 0;
}