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
void dlist_imprimir(Dlist lista);
Dlist dlist_insert(Dlist list, void* in_data);
Dlist dlist_append(Dlist list, void* in_data);
Dlist dlist_delete(Dlist list, void* del_data);
Dlist dlist_destroy(Dlist list);

typedef Dlist Stack;

Stack stack_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit);
int stack_empty(Stack stack);
Stack push(Stack stack, void* in_data);
Stack pop(Stack stack);
void* top(Stack stack);

typedef Dlist Queue;

Queue queue_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit);
int queue_empty(Queue queue); 
Queue enqueue(Queue queue, void* in_data);
void* front(Queue queue);
Queue dequeue(Queue queue);

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
BTree btree_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit);
BTree btree_destroy(BTree root);
int btree_empty(BTree root);
int btree_leaf(BTree root);
BTree btree_max(BTree root);
BTree btree_min(BTree root);
void btree_traverse(BTree root, TRAVERSE_ORDER order);

/* Funciones específicas para BST */
BTree bst_insert(BTree root, void *in_data);
BTree bst_delete(BTree root, void *del_data);
int btree_nnodes(BTree root);
int btree_find(BTree root, void* find_data);
int btree_deep(BTree root);
int btree_nnodes_deep(BTree root,int deep,int current_deep);

#endif /* STRUCTS_H */