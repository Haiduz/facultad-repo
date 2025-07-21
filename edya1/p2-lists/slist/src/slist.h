#ifndef LISTA_H
#define LISTA_H

typedef struct _Snodo {
    int dato;
    struct _Snodo* sig;
} Snodo;

typedef Snodo* Slist;

typedef int (*Comparador)(int, int);
typedef void (*FuncionVisitante)(int);
// funciones triviales 

void slist_recorrer(Slist list, FuncionVisitante visita);
void imprime_int(int dato);
Slist slist_crear();  

// Creación y destrucción
Slist slist_crear_nodo(int in_data);
void slist_destruir(Slist header);

// Operaciones básicas
void slist_agregar_inicio(Slist* header, int in_data);
void slist_agregar_final(Slist* nodo, int in_data);
int slist_longitud(Slist nodo);

// Operaciones avanzadas
void slist_insertar(Slist* header, int in_data, int pos);
void slist_eliminar(Slist *header, int pos);
int slist_contiene(Slist *header, int data);
int slist_indice(Slist *header, int data);
void slist_concatenar(Slist* list1, Slist list2);
Slist* slist_intersecar(Slist* list1, Slist* list2);
void slist_ordenar(Slist* list, Comparador funcion);

//funciones comparadoras
int mayor(int a, int b);

#endif