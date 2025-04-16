#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

// Creación y destrucción

// Crea un nuevo nodo con el dato proporcionado.
Slist slist_crear_nodo(int in_data) {
    Slist header = (Snodo*)malloc(sizeof(Snodo));
    header->dato = in_data;
    header->sig = NULL;
    return header;
}

// Libera toda la memoria ocupada por la lista.
void slist_destruir(Slist* header) {
    if(*header == NULL) {
        return;
    }

    Slist siguiente, actual = *header;
    while(actual != NULL) {
        siguiente = actual->sig;  // Guarda referencia al siguiente nodo.
        free(actual);            // Libera el nodo actual.
        actual = siguiente;      // Avanza al siguiente nodo.
    }
    *header = NULL;              // Deja el puntero a lista en NULL.
}

// Operaciones básicas

// Inserta un nodo al inicio de la lista.
void slist_agregar_inicio(Slist* header, int in_data) {
    Slist newhead = slist_crear_nodo(in_data);
    newhead->sig = *header;   // Nuevo nodo apunta al actual primer nodo.
    *header = newhead;        // El header apunta ahora al nuevo nodo.
}

// Inserta un nodo al final de la lista.
void slist_agregar_final(Slist* nodo, int in_data) {
    if(*nodo == NULL) {
        *nodo = slist_crear_nodo(in_data);  // Si la lista está vacía, crea el primer nodo.
        return;
    }

    Slist nuevonodo = *nodo;
    while(nuevonodo->sig != NULL) {   // Busca el último nodo.
        nuevonodo = nuevonodo->sig;
    }
    nuevonodo->sig = slist_crear_nodo(in_data);  // Inserta al final.
}

// Devuelve la cantidad de nodos en la lista.
int slist_longitud(Slist nodo) {
    int contador = 0;
    while(nodo != NULL) {
        contador++;
        nodo = nodo->sig;
    }
    return contador;
}

// Operaciones avanzadas

// Inserta un nodo en una posición específica.
void slist_insertar(Slist* header, int in_data, int pos) {
    if(*header == NULL || pos == 0) {
        slist_agregar_inicio(header, in_data);  // Si la lista está vacía o posición es 0, se agrega al inicio.
        return;
    }
    
    Slist node = slist_crear_nodo(in_data), current = *header;
    // Recorre hasta el nodo anterior a la posición deseada o hasta el final.
    for(int count = 0; count < (pos - 1) && current->sig != NULL; count++, current = current->sig);

    node->sig = current->sig;  // Apunta al nodo que estaba en esa posición.
    current->sig = node;       // Inserta el nuevo nodo.
}

// Elimina un nodo en una posición específica.
void slist_eliminar(Slist *header, int pos) {
    if(*header == NULL) {
        return;
    }

    Slist current = *header, siguiente;

    if(pos == 0) {  // Caso especial: borrar la cabeza de la lista.
        *header = current->sig;
        free(current);
        return;
    }

    int count = 0;
    // Avanza hasta el nodo anterior al que se quiere eliminar.
    while(count < (pos - 1) && current->sig != NULL) {
        current = current->sig;
        count++;
    }

    if(current->sig == NULL) {
        return;  // Posición fuera de rango.
    }

    siguiente = current->sig->sig;  // Guarda el nodo siguiente al que se eliminará.
    free(current->sig);             // Libera el nodo.
    current->sig = siguiente;       // Reconecta la lista.
}

// Busca si un dato existe en la lista.
int slist_contiene(Slist *header, int data) {
    Slist current = *header;
    while(current != NULL) {
        if(current->dato == data) {
            return 1;  // Dato encontrado.
        }
        current = current->sig;
    }
    return 0;  // Dato no encontrado.
}

// Devuelve la posición del primer nodo con el dato dado, o -1 si no existe.
int slist_indice(Slist *header, int data) {
    int count = 0;
    Slist current = *header;
    while(current != NULL) {
        if(current->dato == data) {
            return count;
        }
        count++;
        current = current->sig;
    }
    return -1;  // Dato no encontrado.
}

// Devuelve una nueva lista con los elementos comunes entre dos listas.
// Evita duplicados en el resultado.
Slist* slist_intersecar(Slist* list1, Slist* list2) {
    Slist* result = malloc(sizeof(Slist));
    *result = NULL;

    Slist current = *list1;
    while(current != NULL) {
        // Verifica si el dato está en list2 y no fue ya agregado.
        if(slist_contiene(list2, current->dato) && !slist_contiene(result, current->dato)) {
            slist_agregar_inicio(result, current->dato);
        }
        current = current->sig;
    }
    return result;
}

// Concatena list2 al final de list1.
void slist_concatenar(Slist* list1, Slist list2) {
    if(*list1 == NULL) {  // Si list1 está vacía, simplemente apunta a list2.
        *list1 = list2;
        return;
    }

    Slist current = *list1;
    while(current->sig != NULL) {  // Busca el último nodo.
        current = current->sig;
    }
    current->sig = list2;  // Une list2 al final.
}
