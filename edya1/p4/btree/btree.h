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

void* copiaNBtree(void* NBtree);
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
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitanteTree visit);

#endif /* __BTREE_H__ */
