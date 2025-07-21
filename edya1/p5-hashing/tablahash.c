#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/*
 * Definición de lista doblemente enlazada (DList)
 */
typedef struct _DNodo {
    void* dato;
    struct _DNodo* ant;
    struct _DNodo* sig;
} DNodo;

typedef struct {
    DNodo* primero;
    DNodo* ultimo;
    int longitud;
} DList;

/*
 * Funciones básicas de DList
 */
DList dlist_crear() {
    DList lista = {NULL, NULL, 0};
    return lista;
}

void dlist_destruir(DList lista, FuncionDestructora destr) {
    DNodo* nodo = lista.primero;
    while (nodo != NULL) {
        DNodo* temp = nodo;
        nodo = nodo->sig;
        destr(temp->dato);
        free(temp);
    }
}

/*
 * Inserción ordenada en DList
 */
DList dlist_insertar_ordenado(DList lista, void* dato, FuncionCopiadora copia, 
                             FuncionComparadora cmp) {
    DNodo* nuevo = malloc(sizeof(DNodo));
    nuevo->dato = copia(dato);
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    
    // Caso lista vacía
    if (lista.primero == NULL) {
        lista.primero = nuevo;
        lista.ultimo = nuevo;
        lista.longitud = 1;
        return lista;
    }
    
    // Buscar posición de inserción
    DNodo* actual = lista.primero;
    while (actual != NULL && cmp(actual->dato, dato) < 0) {
        actual = actual->sig;
    }
    
    // Insertar al principio
    if (actual == lista.primero) {
        nuevo->sig = lista.primero;
        lista.primero->ant = nuevo;
        lista.primero = nuevo;
    }
    // Insertar al final
    else if (actual == NULL) {
        nuevo->ant = lista.ultimo;
        lista.ultimo->sig = nuevo;
        lista.ultimo = nuevo;
    }
    // Insertar en medio
    else {
        nuevo->sig = actual;
        nuevo->ant = actual->ant;
        actual->ant->sig = nuevo;
        actual->ant = nuevo;
    }
    
    lista.longitud++;
    return lista;
}

/*
 * Búsqueda binaria en DList ordenada
 */
void* dlist_buscar_binario(DList lista, void* dato, FuncionComparadora cmp) {
    int inicio = 0;
    int fin = lista.longitud - 1;
    
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        
        // Avanzar hasta la posición media
        DNodo* actual = lista.primero;
        for (int i = 0; i < medio && actual != NULL; i++) {
            actual = actual->sig;
        }
        
        if (actual == NULL) return NULL;
        
        int comparacion = cmp(actual->dato, dato);
        
        if (comparacion == 0) {
            return actual->dato;
        } else if (comparacion < 0) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    
    return NULL;
}

/*
 * Eliminación de un elemento en DList
 */
DList dlist_eliminar(DList lista, void* dato, FuncionDestructora destr, 
                    FuncionComparadora cmp) {
    DNodo* actual = lista.primero;
    
    while (actual != NULL) {
        if (cmp(actual->dato, dato) == 0) {
            // Caso único elemento
            if (lista.primero == lista.ultimo) {
                lista.primero = NULL;
                lista.ultimo = NULL;
            }
            // Caso primer elemento
            else if (actual == lista.primero) {
                lista.primero = actual->sig;
                lista.primero->ant = NULL;
            }
            // Caso último elemento
            else if (actual == lista.ultimo) {
                lista.ultimo = actual->ant;
                lista.ultimo->sig = NULL;
            }
            // Caso medio
            else {
                actual->ant->sig = actual->sig;
                actual->sig->ant = actual->ant;
            }
            
            destr(actual->dato);
            free(actual);
            lista.longitud--;
            return lista;
        }
        actual = actual->sig;
    }
    
    return lista;
}

/*
 * Nueva definición de CasillaHash con DList
 */
typedef struct {
    DList lista;
} CasillaHash;

/*
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
    CasillaHash *elems;
    unsigned numElems;
    unsigned capacidad;
    FuncionCopiadora copia;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionHash hash;
};

/*
 * Crea una nueva tabla hash vacía, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                         FuncionComparadora comp, FuncionDestructora destr,
                         FuncionHash hash) {
    TablaHash tabla = malloc(sizeof(struct _TablaHash));
    assert(tabla != NULL);
    tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
    assert(tabla->elems != NULL);
    tabla->numElems = 0;
    tabla->capacidad = capacidad;
    tabla->copia = copia;
    tabla->comp = comp;
    tabla->destr = destr;
    tabla->hash = hash;

    // Inicializamos las casillas con listas vacías
    for (unsigned idx = 0; idx < capacidad; ++idx) {
        tabla->elems[idx].lista = dlist_crear();
    }

    return tabla;
}

/*
 * Retorna el número de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/*
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/*
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {
    // Destruir cada una de las listas
    for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
        dlist_destruir(tabla->elems[idx].lista, tabla->destr);
    }

    // Liberar el arreglo de casillas y la tabla
    free(tabla->elems);
    free(tabla);
}

/*
 * Inserta un dato en la tabla, manteniendo el orden
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;
    
    // Insertar ordenadamente en la lista
    tabla->elems[idx].lista = dlist_insertar_ordenado(tabla->elems[idx].lista, 
                                                    dato, tabla->copia, tabla->comp);
    tabla->numElems++;
}

/*
 * Busca un dato en la tabla usando búsqueda binaria
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;
    return dlist_buscar_binario(tabla->elems[idx].lista, dato, tabla->comp);
}

/*
 * Elimina un dato de la tabla
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;
    DList lista_original = tabla->elems[idx].lista;
    
    tabla->elems[idx].lista = dlist_eliminar(tabla->elems[idx].lista, 
                                           dato, tabla->destr, tabla->comp);
    
    // Si la lista cambió, decrementar el contador
    if (lista_original.longitud != tabla->elems[idx].lista.longitud) {
        tabla->numElems--;
    }
}