#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>

/* Definición de tipos de función */
typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

/* Estructura de lista */
// OBS: se hace simplemente enlazada porque se implementara como pila y cola

typedef struct _DNode{
    void* data;
    struct _DNode* next;
    struct _DNode* prev;
}_DNode;

typedef struct {
    struct _DNode* first;
    struct _DNode* last;
    FuncionCopiadora copy;
    FuncionComparadora cmp;
    FuncionDestructora destroy;
    FuncionVisitante visit;
}Dlist;

/* Funciones basicas lista simplemente enlazada*/
Dlist dlist_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit);
int dlist_empty(Dlist list);
Dlist dlist_insert(Dlist list, void* in_data);
Dlist dlist_append(Dlist list, void* in_data);
Dlist dlist_delete(Dlist list, void* del_data);

typedef Dlist Stack;

Stack stack_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit);
int stack_empty(Stack stack);
Stack push(Stack stack, void* in_data);
void* pop(Stack* stack);
void* peek(Stack stack);

typedef Dlist Queue;

Queue enqueue(Queue queue, void* in_data);
void* dequeue(Queue* queue);

/* Enumeración para órdenes de recorrido */
typedef enum {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    BFS
} TRAVERSE_ORDER;

/* Estructura del nodo del árbol */
typedef struct _BTNode {
    void *data;
    struct _BTNode *left;
    struct _BTNode *right;
} _BTNode;

typedef struct{
    _BTNode* node;
    FuncionCopiadora copy;
    FuncionComparadora cmp;
    FuncionDestructora destroy;
    FuncionVisitante visit;
}BTree;

/* Funciones básicas del árbol binario */
BTree btree_create(void);
int btree_empty(BTree root);
int btree_leaf(BTree root);
BTree btree_max(BTree root);
BTree btree_min(BTree root);
void btree_traverse(BTree root, TRAVERSE_ORDER order);

/* Funciones específicas para BST */
BTree bst_insert(BTree root, void *in_data);
BTree bst_delete(BTree root, void *del_data);

#endif /* STRUCTS_H */