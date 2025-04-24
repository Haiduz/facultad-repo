[1mdiff --git a/edya1/p2/slist/main b/edya1/p2/slist/main[m
[1mindex 950c977..23fd169 100755[m
Binary files a/edya1/p2/slist/main and b/edya1/p2/slist/main differ
[1mdiff --git a/edya1/p2/slist/main.c b/edya1/p2/slist/main.c[m
[1mindex ed51f3d..ac98201 100644[m
[1m--- a/edya1/p2/slist/main.c[m
[1m+++ b/edya1/p2/slist/main.c[m
[36m@@ -2,30 +2,55 @@[m
 #include <stdio.h>[m
 [m
 int main() {[m
[31m-    // Ejemplo básico de uso[m
[31m-    Slist lista = NULL;[m
[31m-    [m
[32m+[m
[32m+[m[32m    Slist *lista;[m
[32m+[m[32m    Slist *lista2;[m
[32m+[m[32m    (*lista) = NULL;[m
[32m+[m[32m    (*lista2) = NULL;[m
     // Agregar elementos[m
[31m-    slist_agregar_final(&lista, 10);[m
[31m-    slist_agregar_final(&lista, 20);[m
[31m-    slist_agregar_inicio(&lista, 5);[m
[32m+[m[32m    slist_agregar_inicio(lista2, 3);[m
[32m+[m[32m    slist_agregar_inicio(lista2, 2);[m
[32m+[m[32m    slist_agregar_inicio(lista2, 1);[m
[32m+[m[32m    slist_agregar_final(lista2, 4);[m
[32m+[m[41m  [m
[32m+[m[32m    slist_agregar_inicio(lista, 3);[m
[32m+[m[32m    slist_agregar_inicio(lista, 2);[m
[32m+[m[32m    slist_agregar_inicio(lista, 1);[m
[32m+[m[32m    slist_agregar_final(lista, 4);[m
     [m
     // Insertar en posición específica[m
[31m-    slist_insertar(&lista, 15, 2);[m
[32m+[m[32m    slist_insertar(lista, 15, 2);[m
     [m
     // Mostrar longitud[m
[31m-    printf("Longitud de la lista: %d\n", slist_longitud(lista));[m
[32m+[m[32m    //printf("Longitud de la lista: %d\n", slist_longitud(*lista));[m
     [m
     // Verificar contenido[m
[31m-    if(slist_contiene(&lista, 20)) {[m
[32m+[m[32m    if(slist_contiene(lista, 20)) {[m
         printf("El 20 está en la lista\n");[m
     }[m
     [m
     // Obtener índice[m
[31m-    printf("Índice del 15: %d\n", slist_indice(&lista, 15));[m
[32m+[m[32m    printf("Índice del 15: %d\n", slist_indice(lista, 15));[m
     [m
[32m+[m[32m    // imprime lista[m
[32m+[m[32m    slist_recorrer((*lista), imprime_int);[m
[32m+[m[32m    puts("");[m
[32m+[m[32m    slist_recorrer((*lista2), imprime_int);[m
[32m+[m[32m    puts("");[m
[32m+[m
[32m+[m[32m    //concatena y ordena[m
[32m+[m[32m    slist_concatenar(lista, (*lista2));[m
[32m+[m[32m    slist_recorrer((*lista), imprime_int);[m
[32m+[m[32m    puts("");[m
[32m+[m
[32m+[m[32m    slist_ordenar(lista, mayor);[m
[32m+[m[32m    slist_recorrer((*lista), imprime_int);[m
[32m+[m[32m    puts("");[m
[32m+[m
[32m+[m
     // Limpiar memoria[m
[31m-    slist_destruir(&lista);[m
[32m+[m[32m    slist_destruir(lista);[m
[32m+[m[32m    //slist_destruir(lista2);[m
     [m
     return 0;[m
 }[m
\ No newline at end of file[m
[1mdiff --git a/edya1/p2/slist/src/slist.c b/edya1/p2/slist/src/slist.c[m
[1mindex 2c85135..0ddb82a 100644[m
[1m--- a/edya1/p2/slist/src/slist.c[m
[1m+++ b/edya1/p2/slist/src/slist.c[m
[36m@@ -2,6 +2,22 @@[m
 #include <stdio.h>[m
 #include <stdlib.h>[m
 [m
[32m+[m[32m// opereacion triviales[m[41m [m
[32m+[m
[32m+[m[32mvoid slist_recorrer(Slist lista, FuncionVisitante visit) {[m
[32m+[m[32m    for (Snodo *nodo = lista; nodo != NULL; nodo = nodo->sig)[m
[32m+[m[32m      visit(nodo->dato);[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32mvoid imprime_int(int dato) {[m
[32m+[m[32m    printf("%d ", dato);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mSlist slist_crear() {[m
[32m+[m[32m    return NULL;[m
[32m+[m[32m  }[m
[32m+[m[41m  [m
[32m+[m
 // Creación y destrucción[m
 [m
 // Crea un nuevo nodo con el dato proporcionado.[m
[36m@@ -163,3 +179,37 @@[m [mvoid slist_concatenar(Slist* list1, Slist list2) {[m
     }[m
     current->sig = list2;  // Une list2 al final.[m
 }[m
[32m+[m
[32m+[m[32mint mayor(int a, int b){[m
[32m+[m[32m    return a-b;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid slist_ordenar(Slist* lista, Comparador func) {[m
[32m+[m[32m    // Caso base lista vacia o con un solo elemento[m
[32m+[m[32m    if(lista == NULL || *lista == NULL || (*lista)->sig == NULL) {[m
[32m+[m[32m        return;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    Slist actual = *lista;[m
[32m+[m[32m    Slist minimo = actual;[m
[32m+[m[32m    Slist prev_min = NULL;[m[41m [m
[32m+[m[32m    // Encontrar el nodo con el valor minimo[m
[32m+[m[32m    // siempre me estoy fijando un valor adelante de donde estoy parado[m
[32m+[m[32m    while(actual->sig != NULL) {[m
[32m+[m[32m        if(func(actual->sig->dato, minimo->dato) < 0) {[m
[32m+[m[32m            prev_min = actual;[m
[32m+[m[32m            minimo = actual->sig;[m
[32m+[m[32m        }[m
[32m+[m[32m        actual = actual->sig;[m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    // Si el minimo no es el primero intercambia[m
[32m+[m[32m    if(minimo != (*lista)) {[m
[32m+[m[32m        prev_min->sig = minimo->sig;[m
[32m+[m[32m        minimo->sig = (*lista);[m[41m  [m
[32m+[m[32m        (*lista) =  minimo;[m[41m        [m
[32m+[m[32m    }[m
[32m+[m
[32m+[m[32m    // recursion[m[41m [m
[32m+[m[32m    slist_ordenar(&((*lista)->sig), func);[m
[32m+[m[32m}[m
\ No newline at end of file[m
[1mdiff --git a/edya1/p2/slist/src/slist.h b/edya1/p2/slist/src/slist.h[m
[1mindex 86efe32..1567c33 100644[m
[1m--- a/edya1/p2/slist/src/slist.h[m
[1m+++ b/edya1/p2/slist/src/slist.h[m
[36m@@ -8,6 +8,14 @@[m [mtypedef struct _Snodo {[m
 [m
 typedef Snodo* Slist;[m
 [m
[32m+[m[32mtypedef int (*Comparador)(int, int);[m
[32m+[m[32mtypedef void (*FuncionVisitante)(int);[m
[32m+[m[32m// funciones triviales[m[41m [m
[32m+[m
[32m+[m[32mvoid slist_recorrer(Slist list, FuncionVisitante visita);[m
[32m+[m[32mvoid imprime_int(int dato);[m
[32m+[m[32mSlist slist_crear();[m[41m  [m
[32m+[m
 // Creación y destrucción[m
 Slist slist_crear_nodo(int in_data);[m
 void slist_destruir(Slist* header);[m
[36m@@ -22,7 +30,11 @@[m [mvoid slist_insertar(Slist* header, int in_data, int pos);[m
 void slist_eliminar(Slist *header, int pos);[m
 int slist_contiene(Slist *header, int data);[m
 int slist_indice(Slist *header, int data);[m
[31m-Slist* slist_intersecar(Slist* list1, Slist* list2);[m
 void slist_concatenar(Slist* list1, Slist list2);[m
[32m+[m[32mSlist* slist_intersecar(Slist* list1, Slist* list2);[m
[32m+[m[32mvoid slist_ordenar(Slist* list, Comparador funcion);[m
[32m+[m
[32m+[m[32m//funciones comparadoras[m
[32m+[m[32mint mayor(int a, int b);[m
 [m
 #endif[m
\ No newline at end of file[m
[1mdiff --git a/edya1/p2/slist/src/slist.o b/edya1/p2/slist/src/slist.o[m
[1mindex 7ab0d01..bad3c60 100644[m
Binary files a/edya1/p2/slist/src/slist.o and b/edya1/p2/slist/src/slist.o differ
