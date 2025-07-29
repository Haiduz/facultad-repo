#include "header.h"

Hashtable hashtable_create(int size ,FuncionCopiadora copy, FuncionComparadora cmp, FuncionDestructora destroy,
FuncionVisitante visit, FuncionHash hash){
    Hashtable table = malloc(sizeof(_Hashtable));
    table->elements = calloc(size, sizeof(HashSlot));
    table->capacity = size;
    table->occupied = 0;
    table->copy = copy;
    table->cmp = cmp;
    table->destroy = destroy;
    table->visit =visit;
    table->hash = hash;
    return table;
}

void hashtable_destroy(Hashtable table) {
    if (!table) return;  // Verificar tabla nula
    if (!table->elements) {  // Si elements es NULL, solo liberar la tabla
        free(table);
        return;
    }

    for (int i = 0; i < table->capacity; i++) {
        if (table->elements[i]) {
            if (table->elements[i]->data && table->destroy) {  // Verificar destroy
                table->destroy(table->elements[i]->data);
            }
            free(table->elements[i]);
        }
    }
    free(table->elements);
    free(table);
}

void hashtable_insert(Hashtable table, void* in_data){
    if(!table || !in_data || !table->elements || !table->cmp) return;
    unsigned index = table->hash(in_data);
    if(!table->elements[index]){
        // no hay nada guardado en elemets[index], table->elements[index] == NULL   
        table->elements[index] = malloc(sizeof(_HashSlot));
        table->elements[index]->data = table->copy? table->copy(in_data) : in_data;
        table->elements[index]->deleted = 0; /* convencion 0 => valor autentico de la casilla , 1 => valor hecho por probing*/ 
        return;
    }else if(!table->elements[index]->data){
        // espacio de memoria ya reservado, pero la casilla en el dato esta guardando NULL
        table->elements[index]->data = table->copy? table->copy(in_data) : in_data;
        table->elements[index]->deleted = 0; /* convencion 0 => valor autentico de la casilla , 1 => valor hecho por probing*/
    }else if(table->cmp(table->elements[index]->data, in_data) == 0){
        // hay algo guardado en la casilla, que es exactamente igual al dato que quiero ingresar, sobreescribo
        table->destroy(table->elements[index]->data);
        table->elements[index]->data = table->copy? table->copy(in_data) : in_data;
        table->elements[index]->deleted = 0; /* convencion 0 => valor autentico de la casilla , 1 => valor hecho por probing*/
    }
}