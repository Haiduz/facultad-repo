#include "header.h"

/* DEFINICIONES DLIST*/

Dlist dlist_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit){ 
    Dlist list = { NULL, NULL, copy, cmp, destroy, visit};
    return list;
};

int dlist_empty(Dlist list) {
    return list.first == NULL && list.last == NULL; 
}
void dlist_imprimir(Dlist lista) {
    _DNode* actual = lista.first;
    while (actual) {
        if (lista.visit) lista.visit(actual->data);
        actual = actual->next;
    }
}

// INSERT Y APPEND NO DEPENDEN DE LA FUNCION CMP NI LA FUNCION COPIA

Dlist dlist_insert(Dlist list, void* in_data) {
    // agrega el inicio de la lista exclusivamente
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
    // agrega al final de la lista exclusivamente
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
Dlist dlist_delete(Dlist list, void* del_data) {
    // Casos base: lista vacía, dato NULL o función de comparación NULL
    if (dlist_empty(list) || !del_data || !list.cmp) return list;

    _DNode* current = list.first;

    // Buscar el nodo a eliminar
    while (current != NULL) {
        if (list.cmp(current->data, del_data) == 0) {
            // Caso 1: Eliminar el primer nodo
            if (current == list.first) {
                _DNode* temp = list.first;
                list.first = list.first->next;
                if (list.first != NULL) {
                    list.first->prev = NULL;
                } else {
                    // La lista queda vacía
                    list.last = NULL;
                }
                if (list.destroy) list.destroy(temp->data);
                free(temp);
                return list;
            }
            // Caso 2: Eliminar el último nodo
            else if (current == list.last) {
                _DNode* temp = list.last;
                list.last = list.last->prev;
                list.last->next = NULL;
                if (list.destroy) list.destroy(temp->data);
                free(temp);
                return list;
            }
            // Caso 3: Eliminar un nodo intermedio
            else {
                _DNode* temp = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (list.destroy) list.destroy(temp->data);
                free(temp);
                return list;
            }
        }
        current = current->next;
    }

    // Si no se encontró el dato, retornar la lista sin cambios
    return list;
}

Dlist dlist_destroy(Dlist list){  // Recibir por puntero
    _DNode* node = list.first;
    while(node != NULL){
        _DNode* temp = node;
        node = node->next;
        if(list.destroy) list.destroy(temp->data);
        free(temp);
    }
    list.first = NULL;  // Reiniciar punteros
    list.last = NULL;
    return list;
}

/* DEFINICIONES STACK */

Stack stack_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit){
    Stack new_stack = { NULL, NULL, copy, cmp, destroy, visit};
    return new_stack;
}

int stack_empty(Stack stack){
    return stack.first == NULL && stack.last == NULL;
}

Stack push(Stack stack, void* int_data){
    return dlist_insert(stack, int_data);
}

Stack pop(Stack stack) {
    if (dlist_empty(stack)) return stack;
    // busco modificarla para que depende de la funcion copia y que elimine derectamente el top
    _DNode* temp = stack.first;
    // sabemos que stack tiene al menos un nodo
    stack.first = stack.first->next; 
    if(stack.first->next){
        stack.first->prev = NULL;
    }else{
        stack.last = NULL;
    }
    if(stack.destroy)stack.destroy(temp->data);
    free(temp);
    return stack;
}

void* top(Stack stack) {
    return dlist_empty(stack) ? NULL : stack.first->data;
}

/* DEFINICIONES QUEUE */

Queue queue_create(FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy, FuncionVisitante visit){
    Queue new_queue = {copy, cmp, destroy, visit};
    return new_queue;
}

int queue_empty(Queue queue){
    return queue.first == NULL && queue.last == NULL;
}

Queue enqueue(Queue queue, void* in_data){
    return dlist_append(queue, in_data);  
}

void* front(Queue queue){
    return queue_empty(queue) ? NULL : queue.first->data;
}

Queue dequeue(Queue queue) {
    if (dlist_empty(queue)) return queue;
    
    _DNode* temp = queue.first;
    
    // Caso de un solo nodo
    if (queue.first == queue.last) {
        queue.first = queue.last = NULL;
    } else {
        queue.first = queue.first->next;
        queue.first->prev = NULL;
    }
    
    if (queue.destroy) queue.destroy(temp->data);
    free(temp);
    return queue;
}