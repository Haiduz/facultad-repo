#include "header.h"

/* DEFINICIONES DLIST*/

Dlist dlist_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit){ 
    Dlist list = { NULL, NULL, copy, cmp, destroy, visit};
    return list;
};

int dlist_empty(Dlist list) {
    return list.first == NULL; 
}

Dlist dlist_insert(Dlist list, void* in_data) {
    if (!in_data) return list;  
    _DNode* new_node = malloc(sizeof(struct _DNode));
    if (!new_node) return list;  
    // si la funcion copia es NULL, no hace copia fisica, directamente guarda el dato
    new_node->data = list.copy ? list.copy(in_data) : in_data;
    new_node->next = list.first;
    new_node->prev = NULL;
    if (dlist_empty(list)) {
        list.last = new_node;  
    }else{
        list.first->prev = new_node;
    }
    list.first = new_node;

    return list;
}
Dlist dlist_append(Dlist list, void* in_data){
    if(!in_data) return list;
    if(dlist_empty(list)) return dlist_insert(list, in_data);
    // entonces existe un ultimo nodo o hay al menos uno
    _DNode* new_node = malloc(sizeof(struct _DNode));
    if(!new_node) return list;
    // si la funcion copia es NULL, no hace copia fisica, directamente guarda el dato
    new_node->data = list.copy? list.copy(in_data) : in_data;
    new_node->next = NULL;
    new_node->prev = list.last;
    list.last->next = new_node;
    list.last = new_node;
    return list;
}
Dlist dlist_delete(Dlist list, void* del_data){
    // la unica excepcion es que destroy sea NULL, con el correcto flujo se usa cuando 
    // no se hizo copia fisica del dato, no se quiere liberar el dato y se quiere eliminar
    // el mismo de la lista
    if(dlist_empty(list) || !del_data || !list.cmp) return list;
    if(list.cmp(list.first->data, del_data) == 0){
        _DNode* temp = list.first;
        if(list.first->next == NULL){
            // considerar caso de un solo nodo
            list.first = list.last = NULL;
            list.destroy(temp->data);
            free(temp);
            return list; 
        }
        // existe un segundo nodo
        list.first->next->prev = NULL;
        list.first = list.first->next;
        list.destroy(temp->data);
        free(temp);
        return list;
    }else if(list.cmp(list.last->data, del_data) == 0){
        // nos ahorramos el caso que sea una lista con un solo nodo en la implementacion anterior
        _DNode* temp = list.last;
        list.last->prev->next = NULL;
        list.last = list.last->prev;
        list.destroy(temp->data);
        free(temp);
        return list;
    }else{
        // QUEDA MODIFICAR ELIMINAR UNO DEL MEDIO SI QUERES IMPLEMENTAR ENCADENAMIENTO PARA HASHING 
        // SABEMOS QUE EL NODO A ELIMINAR NO ES FIRST NI LAST, ENTONCES SI O SI SON AL MENOS TRES NODOS
        return list;
    }
}

/* DEFINICIONES STACK */

Stack stack_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit){
    Stack new_stack = { NULL, NULL, copy, cmp, destroy, visit};
    return new_stack;
}

int stack_empty(Stack stack){
    return stack.first == NULL;
}

Stack push(Stack stack, void* int_data){
    return dlist_insert(stack, int_data);
}

void* pop(Stack* stack) {
    if (dlist_empty(*stack)) return NULL;
    
    void* data = stack->first->data;
    *stack = dlist_delete(*stack, data);
    return data;
}

void* peek(Stack stack) {
    return dlist_empty(stack) ? NULL : stack.first->data;
}

/* DEFINICIONES QUEUE */

Queue enqueue(Queue queue, void* in_data){
    return dlist_insert(queue, in_data);
}
void* dequeue(Queue* queue){
    if(dlist_empty(*queue)) return NULL;
    void* data = queue->last->data;
    *queue = dlist_delete(*queue, queue->last->data);
    return data;
}