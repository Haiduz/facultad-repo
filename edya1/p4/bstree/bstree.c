#include "bstree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq, *der;
};

/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() { return NULL; }

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return bstree_buscar(raiz->izq, dato, comp);
  else // raiz->dato < dato
    return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia,
                       FuncionComparadora comp) {
  if (raiz == NULL) { // insertar el dato en un nuevo nodo
    struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
    raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden,
                     FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->izq, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_IN)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->der, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_POST)
      visita(raiz->dato, extra);
  }
} 

//Implemente una funci´on bstree eliminar que elimine, si es posible, 
// un elemento del arbol. Debera
//  garantizar que el ´arbol resultante sea nuevamente un ABB
int es_hoja(BSTree nodo) {
  return nodo->izq == NULL && nodo->der == NULL;
}

BSTree encontrar_minimo(BSTree nodo) {
  if (nodo == NULL) return NULL;
  
  while (nodo->izq != NULL) {
      nodo = nodo->izq;
  }
  
  return nodo;
}

BSTree encontrar_maximo(BSTree nodo) {
  if (nodo == NULL) return NULL;
  
  while (nodo->der != NULL) {
      nodo = nodo->der;
  }
  
  return nodo;
}

BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora compara, FuncionDestructora destruye) {
  // arbol vacio
  if (arbol == NULL) return NULL;

  int cmp = compara(dato, arbol->dato);
  // truquiniii truquito
  if (cmp < 0) {
      arbol->izq = bstree_eliminar(arbol->izq, dato, compara, destruye);
  } else if (cmp > 0) {
      arbol->der = bstree_eliminar(arbol->der, dato, compara, destruye);
  } else {
    // estoy parado sobre el dato a eliminar
      if (es_hoja(arbol)) {
          destruye(arbol->dato);
          free(arbol);
          // vuelve a la llamada anterio de la linea 109 o 107 y reenlaza el padre a null
          return NULL;
      }

      if (arbol->izq == NULL) {
        // tiene un hijo a la derecha
          BSTree temp = arbol->der;
          destruye(arbol->dato);
          free(arbol);
          return temp;
      } else if (arbol->der == NULL) {
        // tiene un hijo a las izquierda  
          BSTree temp = arbol->izq;
          destruye(arbol->dato);
          free(arbol);
          return temp;
      }
      //tiene dos hijs
      BSTree temp = encontrar_minimo(arbol->der);
      // sobreescribo 
      arbol->dato = temp->dato;
      // realmente no se libera el nodo con el dato, pero al pisar la informacion con el min
      // y luego liberar el repedito no se pierde memoria
      arbol->der = bstree_eliminar(arbol->der, temp->dato, compara, destruye);
  }

  return arbol;
}

// hacer funcion que devuelva a direccion del nodo del dato
// buscado, caso contrario NULL

//Implemente bstree k esimo menor que retorne el 
//k-ésimo menor elemento del ABB, con k parámetro.

void* bstree_k_esimo_menor(BSTree arbol, int k, int* contador) {
  if (arbol == NULL) return NULL;
  
  // Recorrer subarbol izquierdo
  void* resultado = bstree_k_esimo_menor(arbol->izq, k, contador);
  if (resultado != NULL) return resultado;
  
  // Visitar nodo actual (inorden)
  (*contador)++;
  if (*contador == k) return arbol->dato;
  
  // Recorrer subarbol derecho
  return bstree_k_esimo_menor(arbol->der, k, contador);
}


// corregir maximos y minimos
int bstree_validar(BSTree arbol, FuncionComparadora cmp, void* min, void* max) {
  if (arbol == NULL) return 1;
  if ((min != NULL && cmp(arbol->dato, min) <= 0) ||
  (max != NULL && cmp(max, arbol->dato) <= 0))return 0;
  return bstree_validar(arbol->izq, cmp, min, arbol->dato) && bstree_validar(arbol->der, cmp, arbol->dato, max);
}