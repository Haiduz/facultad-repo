#include <stdio.h>
#include <stdlib.h>
#include "pilasglist.h"

int main() {
    Pila p = NULL;

    // Crear pila e insertar elementos
    printf("Apilando elementos...\n");
    p = pila_apilar(p, 10);
    p = pila_apilar(p, 20);
    p = pila_apilar(p, 30);
    p = pila_apilar(p, 40);

    printf("Contenido de la pila:\n");
    pila_imprimir(p);  // Debería imprimir: 40 30 20 10
    printf("\n");

    // Mostrar el tope
    printf("Elemento en el tope: %d\n", pila_tope(p));  // Debería ser 40

    // Desapilar y mostrar estado
    printf("Desapilando elementos...\n");
    while (!pila_esvacia(p)) {
        printf("Tope: %d\n", pila_tope(p));
        p = pila_desapilar(p);
        printf("Pila ahora: ");
        pila_imprimir(p);
        printf("\n");
    }

    // Destruir la pila
    pila_destruir(p);
    printf("Pila destruida.\n");

    return 0;
}
