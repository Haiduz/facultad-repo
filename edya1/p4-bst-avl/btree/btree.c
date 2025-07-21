#include "btree.h"
#include "../../p2/glist/glist.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


// revisar el malloc y el free de esta variable
void* btree_copia_ite(void* copiado){
  //copia exlusivamente la direccion del nodo del arbol
  BTree original= (BTree)copiado;
  BTree copia = malloc(sizeof(BTree));
  copia = original;
  return (void*)copia;
}

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteTree visit) {
  if (btree_empty(arbol)) return;
  
  switch (orden) {
    case BTREE_RECORRIDO_PRE:
      visit(arbol->dato);  // Visitar raiz
      btree_recorrer(arbol->left, orden, visit);  // Recorrer subarbol izquierdo
      btree_recorrer(arbol->right, orden, visit); // Recorrer subarbol derecho
    break;
          
    case BTREE_RECORRIDO_IN:
      btree_recorrer(arbol->left, orden, visit);  // Recorrer subarbol izquierdo
      visit(arbol->dato);  // Visitar raiz
      btree_recorrer(arbol->right, orden, visit); // Recorrer subarbol derecho
    break;
          
    case BTREE_RECORRIDO_POST:
      btree_recorrer(arbol->left, orden, visit);  // Recorrer subarbol izquierdo
      btree_recorrer(arbol->right, orden, visit); // Recorrer subarbol derecho
      visit(arbol->dato);  // Visitar raiz
    break;
    
    // Dise˜ne una versi´on iterativa para el caso preorden. 
    //Ayuda: puede utilizar una pila general para guardar los nodos a visitar.
    case BTREE_RECORRIDO_PRE_ITE: {
      // FUNCIONA :DDDD
      if(btree_empty(arbol)) return;
      // la direccion de pila es el header de glist
      GList pila = glist_crear();
      pila = glist_agregar_inicio(pila, arbol, btree_copia_ite);
      while(!glist_vacia(pila)){
        // el nodo del arbol esta en el dato
        BTree actual = (BTree)pila->data;
        pila = glist_eliminar_header(pila,free);
        visit(actual->dato);
        //printf("desapila e imprime %d \n", actual->dato);
        if(actual->right != NULL){
          pila=glist_agregar_inicio(pila,actual->right, btree_copia_ite);
          //printf("apila %d \n", actual->right->dato);
        }
        if(actual->left != NULL){
          pila=glist_agregar_inicio(pila,actual->left, btree_copia_ite);
          //printf("apila %d \n", actual->left->dato);
        }
      }
      glist_destruir(pila, free);  
    break;
    }
    default:
    break;
  }
  return;
}

// devuelve la cantidad de nodos de un arbol
int  btree_nnodos(BTree arbol){
  //no voy a poder reutilizar la fc btree recorrer pq fc visitant
  // toma un entero y devuelve void
  if(btree_empty(arbol)) return 0;
  // suma la ramas del subarbol izq y der
  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
} 

// devuelve 1 si se encuentra el dato 0 si no
int btree_buscar(BTree arbol, int buscado) {
  if (btree_empty(arbol)) return 0;
  if (arbol->dato == buscado) return 1;
  // busca primero en el subarbol izq,sino der, buscar en el der
  if (btree_buscar(arbol->left, buscado)) return 1;  // Si ya se encontro, no es necesario buscar en el derecho
  return btree_buscar(arbol->right, buscado);
}

// COPIA TODO DE EL FOCKING ARBOL
BTree btree_copia(BTree original) {
  if (original == NULL) return NULL;
 
  BTree copia = malloc(sizeof(struct _BTNodo));
  copia->dato = original->dato;
  copia->left = btree_copia(original->left);
  copia->right = btree_copia(original->right);
  return copia;
}


int btree_altura(BTree arbol){
 // devuelve la altura del arbol
 if(arbol == NULL) return 0;
 int a1 = btree_altura(arbol->left) + 1;
 int a2 = btree_altura(arbol->right) + 1;
 return a1 > a2 ? a1 : a2;
}

// SUMA SUMA SUM
int btree_sumar(BTree arbol){
  if( arbol == NULL) return 0;
  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
} 

int btree_nnodos_profundidad(BTree arbol, int profundidad, int profundidad_actual){
  if(btree_empty(arbol))return 0;
  if(profundidad_actual == profundidad) return 1;
  //paso recursivo
  // tiene que sumar la cantidad de nodos en ambos subarboles
  return btree_nnodos_profundidad(arbol->left, profundidad, profundidad_actual + 1) +
         btree_nnodos_profundidad(arbol->right, profundidad, profundidad_actual + 1);
}

//btree profundidad: que retorne la profundidad del nodo que contiene el n´umero dado, y -1 si el
//n´umero no se encuentra en el ´arbol.
int btree_profundidad(BTree arbol, int buscado, int profundidad_actual){
  if(btree_empty(arbol))return -1;
  if(arbol->dato == buscado) return profundidad_actual;
  profundidad_actual++;
  int arbol_izq = btree_profundidad(arbol->left, buscado, profundidad_actual);
  int arbol_der = btree_profundidad(arbol->right, buscado, profundidad_actual);
  return (arbol_izq != -1) ? arbol_izq : arbol_der;
}