#include "btree.h"
#include "../../p2/glist/glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void* copiaNBtree(void* NBtree) {
  BTree original = (BTree)NBtree;
  if (original == NULL) return NULL;

  BTree copia = malloc(sizeof(struct _BTNodo));
  copia->dato = original->dato;
  copia->left = copiaNBtree(original->left);
  copia->right = copiaNBtree(original->right);
  return copia;
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
      if(btree_empty(arbol)) return;
      // la direccion de pila es el header de glist
      GList pila = glist_crear();
      pila = glist_agregar_inicio(pila, arbol, copiaNBtree);
      while(!glist_vacia(pila)){
        // el nodo del arbol esta en el dato
        BTree actual = (BTree)pila->data;
        pila = glist_eliminar_header(pila,free);
        visit(actual->dato);
        //printf("desapila e imprime %d \n", actual->dato);
        if(actual->right != NULL){
          pila=glist_agregar_inicio(pila,actual->right, copiaNBtree);
          //printf("apila %d \n", actual->right->dato);
        }
        if(actual->left != NULL){
          pila=glist_agregar_inicio(pila,actual->left, copiaNBtree);
          //printf("apila %d \n", actual->left->dato);
        }
      }  
    break;
    }
    default:
      assert(0);  // Orden no reconocido
    break;
  }
  return;
}