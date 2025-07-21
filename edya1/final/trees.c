#include "header.h"

/*
    FUNCIONES DE BTREE
*/

BTree btree_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit) {
    BTree tree = { NULL, copy, cmp, destroy, visit };
    return tree;
}

int btree_empty(BTree root) {
    return root.node == NULL;
}

int btree_leaf(BTree root) {
    if (btree_empty(root)) return 0;
    return root.node->left == NULL && root.node->right == NULL;
}
// viaja a la derecha siempre que pueda
BTree btree_max(BTree root) {
    if (btree_empty(root)) return root;
    
    BTree max = root;
    while (max.node->right != NULL) {
        max.node = max.node->right;
    }
    return max;
}
// viaja a la izq siempre que pueda
BTree btree_min(BTree root) {
    if (btree_empty(root)) return root;
    
    BTree min = root;
    while (min.node->left != NULL) {
        min.node = min.node->left;
    }
    return min;
}


void btree_traverse(BTree root, TRAVERSE_ORDER order) {
    if (btree_empty(root)) return;
    
    switch (order) {
        case PRE_ORDER:
            if (root.visit) root.visit(root.node->data);
            btree_traverse((BTree){root.node->left, root.copy, root.cmp, root.destroy, root.visit}, order);
            btree_traverse((BTree){root.node->right, root.copy, root.cmp, root.destroy, root.visit}, order);
        break;
            
        case IN_ORDER:
            btree_traverse((BTree){root.node->left, root.copy, root.cmp, root.destroy, root.visit}, order);
            if (root.visit) root.visit(root.node->data);
            btree_traverse((BTree){root.node->right, root.copy, root.cmp, root.destroy, root.visit}, order);
        break;
            
        case POST_ORDER:
            btree_traverse((BTree){root.node->left, root.copy, root.cmp, root.destroy, root.visit}, order);
            btree_traverse((BTree){root.node->right, root.copy, root.cmp, root.destroy, root.visit}, order);
            if (root.visit) root.visit(root.node->data);
        break;
            
        case BFS:
            if(root.node == NULL) return;
            // Crear cola sin funciones de copia/destrucción
            Queue q_bfs = queue_create(NULL, NULL, NULL, root.visit);
            q_bfs = enqueue(q_bfs, root.node);
    
            while(!queue_empty(q_bfs)) {
                _BTNode* current = (_BTNode*)front(q_bfs);
                if (root.visit) root.visit(current->data);
                q_bfs = dequeue(q_bfs);
        
                if(current->left != NULL) q_bfs = enqueue(q_bfs, current->left);
                if(current->right != NULL) q_bfs = enqueue(q_bfs, current->right);
            }
        break;

        default:
            return;
        break;
    }
}

/*
    FUNCIONES BST
*/

BTree bst_insert(BTree root, void* in_data) {
    if (btree_empty(root)) {
        _BTNode* new_node = malloc(sizeof(_BTNode));
        if (!new_node) return root;
        
        new_node->data = root.copy ? root.copy(in_data) : in_data;
        new_node->left = NULL;
        new_node->right = NULL;
        
        root.node = new_node;
        return root;
    }
    
    if (root.cmp(root.node->data, in_data) >= 0) {
        // hago todo este biribiri porque bst_insert devuelve la estructura Btree
        BTree left = { root.node->left, root.copy, root.cmp, root.destroy, root.visit };
        left = bst_insert(left, in_data);
        // y root.node->left espera un _BTNode* != BTree
        root.node->left = left.node;
    } else {
        BTree right = { root.node->right, root.copy, root.cmp, root.destroy, root.visit };
        right = bst_insert(right, in_data);
        root.node->right = right.node;
    }
    
    return root;
}

BTree bst_delete(BTree root, void* del_data) {
    if (btree_empty(root)) return root;

    if (root.cmp(root.node->data, del_data) > 0) {
        BTree left = { root.node->left, root.copy, root.cmp, root.destroy, root.visit };
        left = bst_delete(left, del_data);
        root.node->left = left.node;
    } else if (root.cmp(root.node->data, del_data) < 0) {
        BTree right = { root.node->right, root.copy, root.cmp, root.destroy, root.visit };
        right = bst_delete(right, del_data);
        root.node->right = right.node;
    } else {
        // caso es una hoja
        if (btree_leaf(root)) {
            if (root.destroy) root.destroy(root.node->data);
            free(root.node);
            return (BTree){ NULL, root.copy, root.cmp, root.destroy, root.visit };
        }
        // caso dos hijos
        if (!btree_empty((BTree){root.node->left, root.copy, root.cmp, root.destroy, root.visit}) && 
            !btree_empty((BTree){root.node->right, root.copy, root.cmp, root.destroy, root.visit})) {
            //
            BTree max_left = btree_max((BTree){root.node->left, root.copy, root.cmp, root.destroy, root.visit});
            void* temp = root.node->data;
            root.node->data = max_left.node->data;
            max_left.node->data = temp;
            // mas biribiri para la recursion y eliminar la hoja
            BTree left = { root.node->left, root.copy, root.cmp, root.destroy, root.visit };
            left = bst_delete(left, del_data);
            root.node->left = left.node;
        } else {
            _BTNode* temp = root.node->left ? root.node->left : root.node->right;
            if (root.destroy) root.destroy(root.node->data);
            free(root.node);
            root.node = temp;
        }
    }
    
    return root;
}

BTree btree_destroy(BTree root) {
    if(!btree_empty(root)){
        btree_destroy((BTree){root.node->left, NULL, NULL, root.destroy, NULL});
        btree_destroy((BTree){root.node->right, NULL, NULL, root.destroy, NULL});
        if(root.destroy)root.destroy(root.node->data);
        free(root.node);
        root.node = NULL;
    }
    return root;
}

int btree_nnodes(BTree root){
    if(btree_empty(root)) return 0;
    return 1 + btree_nnodes((BTree){root.node->right, NULL, NULL, NULL, NULL}) + btree_nnodes((BTree){root.node->left, NULL, NULL, NULL, NULL});
}

int btree_find(BTree root, void* find_data) {
    if(btree_empty(root)) return 0;
    
    int cmp_result = root.cmp(root.node->data, find_data);
    if(cmp_result == 0) {
        return 1; // Encontrado
    }
    else if(cmp_result > 0) { // Buscar en el subárbol izquierdo (valores menores)
        return btree_find((BTree){root.node->left, NULL, root.cmp, NULL, NULL}, find_data);
    }
    else { // Buscar en el subárbol derecho (valores mayores)
        return btree_find((BTree){root.node->right, NULL, root.cmp, NULL, NULL}, find_data);
    }
}

int btree_deep(BTree root){
    if(btree_empty(root)) return 0;
    int a1 = btree_deep((BTree){root.node->left, NULL, NULL, NULL, NULL}) + 1;
    int a2 = btree_deep((BTree){root.node->right, NULL, NULL, NULL, NULL}) + 1;
    return a1 >= a2 ? a1 : a2; 
}

int btree_nnodes_deep(BTree root,int deep,int current_deep){
    if(btree_empty(root)) return 0;
    if(deep == current_deep) return 1;
    return btree_nnodes_deep((BTree){root.node->left, NULL, NULL, NULL, NULL}, deep, current_deep + 1) 
    + btree_nnodes_deep((BTree){root.node->right, NULL, NULL, NULL, NULL}, deep, current_deep + 1);
}

void* bst_k_minor(BTree root, int k) {
    if (btree_empty(root) || k <= 0) return NULL;

    Stack s = stack_create(NULL, NULL, NULL, NULL);
    _BTNode* current = root.node;
    int count = 0;

    while (current != NULL || !stack_empty(s)) {
        // Apilar todos los nodos izquierdos hasta llegar al mínimo
        while (current != NULL) {
            s = push(s, current);
            current = current->left;
        }

        // Procesar el nodo actual (el más pequeño no procesado)
        current = (_BTNode*)top(s);
        s = pop(s);
        count++;

        if (count == k) {
            return current->data; // Encontramos el k-ésimo menor
        }

        // Mover al subárbol derecho
        current = current->right;
    }

    return NULL; // Si k es mayor que el número de nodos
}