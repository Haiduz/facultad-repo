#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE 100

typedef struct _SNodo{
    char* palabra;
    struct _SNodo* sig;
}SNodo;

typedef SNodo* Slist;
typedef Slist CasillaHash;

typedef struct _TablaHash
{
    CasillaHash* arr;
    int ocupados;
    int capacidad;
}_TablaHash;

typedef _TablaHash* TablaHash;

Slist slist_agregar_inicio(Slist lista, char* in_palabra){
    SNodo* nuevonodo= malloc(sizeof(SNodo));

    nuevonodo->palabra = (char*)malloc(strlen(in_palabra)+1);
    strcpy(nuevonodo->palabra, in_palabra);
    nuevonodo->sig = lista;
    lista = nuevonodo;
    return lista;
}


Slist crear_lista(){return NULL;}

void slist_destruir(Slist lista){
    if(lista == NULL) return ;
    slist_destruir(lista->sig);
    free(lista->palabra);
    free(lista);
    // la lista queda apuntando a cualquier lado
}

int slist_buscar(Slist lista, char* buscado){
    if(lista == NULL) return 0;
    while ((lista->sig != NULL) && (strcmp(lista->palabra, buscado) !=0))lista = lista->sig;
    return strcmp(lista->palabra, buscado)==0 ? 1 : 0;
}

Slist slist_eliminar(Slist lista, char* del_palabra){
    if(lista == NULL) return lista;
    if(strcmp(lista->palabra, del_palabra) == 0){
        // caso especial quiero eliminar la primera palabra
        SNodo* temp = lista;
        lista = lista->sig;
        free(temp->palabra);
        free(temp);
        return lista; 
    }
    Slist nodo = lista; // para no perder la referencia de la lista original
    while ((nodo->sig != NULL) && (strcmp(nodo->sig->palabra, del_palabra) !=0))nodo = nodo->sig;
    if(nodo->sig == NULL) return lista; // palabra no encontrada
    // estoy parado en el nodo anterior al eliminar, sin importar que sea el ultimo
    SNodo* temp = nodo->sig;
    nodo->sig = nodo->sig->sig; // como lista->sig != NULL 0 => lista->sig->sig disponible aunque puede ser null
    free(temp->palabra);
    free(temp);
    return lista; 
}

int hash(char* palabra){
    // hashea por los primeros tres caracteres
    int hash = 0;
    for(int i=0; palabra[i] != '\0' && i<3; i++) hash += palabra[i];
    return hash;
}

TablaHash tabla_crear(){
    TablaHash nuevatabla= malloc(sizeof(_TablaHash));
    nuevatabla->arr = calloc(SIZE,sizeof(Slist));
    nuevatabla->capacidad = SIZE;
    nuevatabla->ocupados = 0;
    return nuevatabla;
}

void tabla_eliminar(TablaHash tabla){
    for(int i = 0; i<tabla->capacidad; i++)slist_destruir(tabla->arr[i]);
    free(tabla->arr);
    free(tabla);

}

void tabla_insertar(TablaHash tabla, char* in_palabra){
    if(!tabla || !in_palabra)return;
    int index = hash(in_palabra)%tabla->capacidad;
    if(!slist_buscar(tabla->arr[index], in_palabra)){
        // si no esta, o la lista esta vacia lo agrego al inicio,
        tabla->arr[index] = slist_agregar_inicio(tabla->arr[index], in_palabra);
        tabla->ocupados++;
    } // si la palabra ya se encuentra no la agrega
}

void tabla_eliminar(TablaHash tabla, char* del_palabra){
    if(!tabla || !del_palabra) return;
    int index = hash(del_palabra)%tabla->capacidad;    
    if(slist_buscar(tabla->arr[index], del_palabra)){
        tabla->arr[index] = slist_eliminar(tabla->arr[index], del_palabra);
        return;
    }
    
}

int main(){
    int a = hash("abc\0");
    printf(" %d \n", a);
    a = hash("cbaa\0");
    printf(" %d \n", a);
    Slist lista = slist_agregar_inicio(NULL, "mama\0");
    printf(" %d \n", slist_buscar(NULL, "sol\0"));
    printf(" %d \n", slist_buscar(lista, "mama\0"));
    lista = slist_eliminar(lista, "mama\0");
    printf(" %d \n", slist_buscar(lista, "mama\0"));
}