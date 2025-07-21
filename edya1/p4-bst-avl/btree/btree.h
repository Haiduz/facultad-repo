#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitanteTree)(int dato);

// se tiene solo la dir de los dos hijos
struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST,
  BTREE_RECORRIDO_PRE_ITE
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteTree visit);

// retorna la cantidad de nodos de un arbol
int  btree_nnodos(BTree arbol);

//btree buscar: que retorne 1 si el 
//numero dado se encuentra en el arbol, y 0 en caso contrario.
int btree_buscar(BTree arbol, int buscado);

BTree btree_copia(BTree NBtree);

//btree altura: que retorne la altura del ´arbol.
int btree_altura(BTree arbol);

//btree sumar: que retorne la suma total de los datos del arbol.
int btree_sumar(BTree arbol);

// devuelve la cantidad de nodos en la profundidad especificada
int btree_nnodos_profundidad(BTree arbol, int profundidad, int profundidad_actual);

//btree profundidad: que retorne la profundidad del nodo que contiene el n´umero dado, y -1 si el
//n´umero no se encuentra en el ´arbol.
int btree_profundidad(BTree arbol, int buscado, int profundidad_actual);
#endif /* __BTREE_H__ */