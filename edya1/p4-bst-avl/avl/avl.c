#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Estructura del nodo del arbol AVL.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * un puntero al nodo raiz del subarbol derecho (der), y
 * un entero para representar la altura del arbol (altura)
 */
typedef struct _AVL_Nodo {
  void* dato;
  struct _AVL_Nodo* izq, * der;
  int altura;
} AVL_Nodo;

/**
 * Estructura del arbol AVL.
 * Tiene un puntero al nodo raiz (raiz),
 * un puntero a funcion (copia) que recibe un dato y retorna un puntero con la
 * direccion de memoria de una copia fisica del dato,
 * un puntero a funcion (comp) que compara dos datos y retorna un entero
 * negativo si el primero es menor que el segundo, 0 si son iguales, y un entero
 * positivo en caso contrario,
 * y un puntero a una funcion (destr) que recibe un dato y lo destruye.
 * En esta implementación, los punteros a funcion necesarios para manipular los
 * datos se mantienen en la estructura para evitar pasarlos por parametro a las
 * demas funciones.
 */
struct _AVL {
  AVL_Nodo* raiz;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
};

/**
 * avl_crear: Retorna un arbol AVL vacio
 */
AVL avl_crear(FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr) {
  // 4 punteros, crea arbol vacion asiq no hace malloc de AVL_NODO
  AVL arbol = malloc(sizeof(struct _AVL));
  assert(arbol != NULL);
  arbol->raiz = NULL;
  // observacion de la linea 28, se guarda en 
  arbol->copia = copia;
  arbol->comp = comp;
  arbol->destr = destr;
  return arbol;
}

/**
 * avl_destruir: Destruye el arbol y sus datos.
 */
static void avl_nodo_destruir(AVL_Nodo* raiz, FuncionDestructora destr) {
  // no estoy pasando como parametro AVL, sino que AVL_NODO*, es necesario pasar
  // como argumento la funcion destructora
  if (raiz != NULL) {
    // destruir los nodos en postorder
    avl_nodo_destruir(raiz->izq, destr);
    avl_nodo_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
}
void avl_destruir(AVL arbol) {
  avl_nodo_destruir(arbol->raiz, arbol->destr);
  // luego de destruir todos los AVL_NODO* libera lo reservado en avl_crear
  free(arbol);
}

/**
 * avl_buscar: Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
static int avl_nodo_buscar(AVL_Nodo* raiz, FuncionComparadora comp,
  void* dato) {
  if (raiz == NULL)
    return 0;

  int c = comp(dato, raiz->dato);
  if (c < 0) // dato < raiz->dato
    return avl_nodo_buscar(raiz->izq, comp, dato);
  else if (c > 0) // dato > raiz->dato
    return avl_nodo_buscar(raiz->der, comp, dato);
  else // dato == raiz->dato
    return 1;
}
// hace la fc dos veces para que la reutilizacion sea mas sencilla
int avl_buscar(AVL arbol, void* dato) {
  return avl_nodo_buscar(arbol->raiz, arbol->comp, dato);
}

/**
 * avl_nodo_altura: Funcion interna que retorna la altura del arbol.
 * La altura del arbol vacio se define como -1.
 */
static int avl_nodo_altura(AVL_Nodo* raiz) {
  return (raiz == NULL ? -1 : raiz->altura);
}

/**
 * avl_nodo_max_altura_hijos: Funcion interna que retorna la maxima altura de
 * los hijos.
 */
static unsigned int avl_nodo_max_altura_hijos(AVL_Nodo* raiz) {
  assert(raiz != NULL);
  int alturaIzq = avl_nodo_altura(raiz->izq);
  int alturaDer = avl_nodo_altura(raiz->der);
  return (alturaIzq < alturaDer ? alturaDer : alturaIzq);
}

/**
 * avl_nodo_factor_balance: Funcion interna que retorna el factor de balance de
 * un nodo.
 */
static int avl_nodo_factor_balance(AVL_Nodo* raiz) {
  assert(raiz != NULL);
  int factor = avl_nodo_altura(raiz->der) - avl_nodo_altura(raiz->izq);
  assert(-2 <= factor && factor <= 2);
  return factor;
}

/**
 * avl_nodo_rotacion_simple_izq: Funcion interna que realiza una rotacion simple
 * a izquierda y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_izq(AVL_Nodo* raiz) {  //
  // hijo derecho del nodo desbalanceado A. llamemos B                        
  AVL_Nodo* hijoDer = raiz->der;
  assert(hijoDer != NULL);

  // Movemos subarabol izquierdo de B para que sea subarbol derecha de A 
  raiz->der = hijoDer->izq;
  // B se convierte en el nuevo padre de A
  hijoDer->izq = raiz;
  
  // actualizar alturas
  raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
  hijoDer->altura = 1 + avl_nodo_max_altura_hijos(hijoDer);
  return hijoDer;
}

/**
 * avl_nodo_rotacion_simple_der: Funcion interna que realiza una rotacion simple
 * a derecha y retorna la nueva raiz.
 */
static AVL_Nodo* avl_nodo_rotacion_simple_der(AVL_Nodo* raiz) {
  // hijo izq del nodo desbalanceado A. llamemos B                        
  AVL_Nodo* hijoIzq = raiz->izq;
  assert(hijoIzq != NULL);

  // Movemos subarabol der de B para que sea subarbol izq de A 
  raiz->izq = hijoIzq->der;
  // B se convierte en el nuevo padre de A
  hijoIzq->der = raiz;
  
  // actualizar alturas
  raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
  hijoIzq->altura = 1 + avl_nodo_max_altura_hijos(hijoIzq);
  return hijoIzq;
  
}

/**
 * avl_nodo_crear: Funcion interna que crea un nuevo nodo y lo retorna.
 * La altura de un nodo hoja es 0.
 */
static AVL_Nodo* avl_nodo_crear(void* dato, FuncionCopiadora copia) {
  AVL_Nodo* nuevoNodo = malloc(sizeof(AVL_Nodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = copia(dato);
  nuevoNodo->izq = nuevoNodo->der = NULL;
  nuevoNodo->altura = 0;
  return nuevoNodo;
}

/**
 * avl_nodo_rebalancear: Reestablece la propiedad de AVL, presuponiendo que:
 *  - el factor de balance esta entre -2 y +2
 *  - los dos hijos cumplen la propiedad de AVL
 */
static AVL_Nodo* avl_nodo_rebalancear(AVL_Nodo* raiz) {
  if (avl_nodo_factor_balance(raiz) == -2) { // Desbalance izquierdo
    if (avl_nodo_factor_balance(raiz->izq) == 1) { // Caso LR
      raiz->izq = avl_nodo_rotacion_simple_izq(raiz->izq);
      raiz->izq->altura = 1 + avl_nodo_max_altura_hijos(raiz->izq);
    }
    raiz = avl_nodo_rotacion_simple_der(raiz);
  }
  else if (avl_nodo_factor_balance(raiz) == 2) { // Desbalance derecho
    if (avl_nodo_factor_balance(raiz->der) == -1) { // Caso RL
      raiz->der = avl_nodo_rotacion_simple_der(raiz->der);
      raiz->der->altura = 1 + avl_nodo_max_altura_hijos(raiz->der);
    }
    raiz = avl_nodo_rotacion_simple_izq(raiz);
  }

  return raiz;
}

/**
 * avl_nodo_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad de los arboles AVL.
 */
static AVL_Nodo* avl_nodo_insertar(AVL_Nodo* raiz, void* dato,
  FuncionCopiadora copia, FuncionComparadora comp) {

  if (raiz == NULL) // insertamos el nuevo elemento
    return avl_nodo_crear(dato, copia);

  int c = comp(dato, raiz->dato);
  if (c < 0) // el dato debe ir en el subarbol izq
    raiz->izq = avl_nodo_insertar(raiz->izq, dato, copia, comp);
  else if (c > 0) // el dato debe ir en el subarbol der
    raiz->der = avl_nodo_insertar(raiz->der, dato, copia, comp);
  else // no agregar elementos repetidos
    return raiz;
  // va actualizando la altura de todos los nodos a medida
  // que vuelve en la recursin 
  raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);

  return avl_nodo_rebalancear(raiz);
} 
void avl_insertar(AVL arbol, void* dato) {
  arbol->raiz = avl_nodo_insertar(arbol->raiz, dato, arbol->copia, arbol->comp);
}

/**
 * avl_validar: Retorna 1 si el arbol cumple la propiedad de los arboles AVL,
 * y 0 en caso contrario.
 * avl_nodo_validar_abb: Funcion interna que retorna 1 si el arbol cumple la
 * propiedad de los arboles BB, y 0 en caso contrario.
 * avl_nodo_validar_altura_y_balance: Funcion interna que retorna 1 si la
 * altura y el factor de balance de los nodos son correctos, y 0 en caso
 * contrario.
 */
static int avl_nodo_validar_abb(AVL_Nodo* raiz, void* min, void* max,
  FuncionComparadora comp) {
  // si la raiz es vacia, retornar exitosamente
  if (raiz == NULL)
    return 1;
  else {
    // sino, validar intervalo
    if (min != NULL && comp(raiz->dato, min) <= 0)
      return 0;
    if (max != NULL && comp(max, raiz->dato) <= 0)
      return 0;
    // y validar subarboles recursivamente

    /* ATENCION!! en la llamada recursiva, cuando recorrde el subarbol 
    izquierdo, toma como maximo el dato de la raiz, y analogo con el
    subarbol derecho, toma como minimo el dato de la raiz
    en ambos casos no toca el minimo si se recorre derecha y maximo 
    cuando se recorre izquieda*/
    return (avl_nodo_validar_abb(raiz->izq, min, raiz->dato, comp) &&
      avl_nodo_validar_abb(raiz->der, raiz->dato, max, comp));
  }
}
static int avl_nodo_validar_altura_y_balance(AVL_Nodo* raiz) {
  if (raiz == NULL) return 1;
  
  if (!avl_nodo_validar_altura_y_balance(raiz->izq)) return 0;
  if (!avl_nodo_validar_altura_y_balance(raiz->der)) return 0;
  
  int altura = 1 + avl_nodo_max_altura_hijos(raiz);
  int balance = avl_nodo_factor_balance(raiz);
  
  return (raiz->altura == altura) && (balance >= -1) && (balance <= 1);
}
int avl_validar(AVL arbol) {
  return (avl_nodo_validar_altura_y_balance(arbol->raiz) &&
    avl_nodo_validar_abb(arbol->raiz, NULL, NULL, arbol->comp));
}

/**
 * avl_recorrer: Recorrido DFS del arbol
 */
static void avl_nodo_recorrer(AVL_Nodo* raiz, AVLRecorrido orden,
  FuncionVisitanteExtra visita, void* extra) {
  if (raiz != NULL) {
    if (orden == AVL_RECORRIDO_PRE)
      visita(raiz->dato, extra);
    avl_nodo_recorrer(raiz->izq, orden, visita, extra);
    if (orden == AVL_RECORRIDO_IN)
      visita(raiz->dato, extra);
    avl_nodo_recorrer(raiz->der, orden, visita, extra);
    if (orden == AVL_RECORRIDO_POST)
      visita(raiz->dato, extra);
  }
}
void avl_recorrer(AVL arbol, AVLRecorrido orden, FuncionVisitanteExtra visita,
  void* extra) {
  avl_nodo_recorrer(arbol->raiz, orden, visita, extra);
}

/**
 * avl_nodo_menor: Devuelve el nodo con el menor dato del árbol.
 */
static AVL_Nodo* avl_nodo_menor(AVL_Nodo* raiz) {
  // OBS: sioso la raiz va a tener dos hijos en la primera llamada
  if (raiz == NULL || raiz->izq == NULL) return raiz;
  return avl_nodo_menor(raiz->izq);
}

/**
 * avl_nodo_eliminar: Elimina el dato del árbol, manteniendo la propiedad de los
 * arboles AVL. No hace nada si el dato no se encuentra en el árbol.
 */
static AVL_Nodo* avl_nodo_eliminar(AVL_Nodo* raiz, void* dato,
  FuncionDestructora destr, FuncionComparadora comp) {

  if (raiz == NULL) // el dato no se encuentra en el árbol
    return NULL;

  int c = comp(dato, raiz->dato);
  if (c < 0) // el dato puede estar en el subárbol izq
    raiz->izq = avl_nodo_eliminar(raiz->izq, dato, destr, comp);
  else if (c > 0) // el dato puede estar en el subárbol der
    raiz->der = avl_nodo_eliminar(raiz->der, dato, destr, comp);
  else { // el dato está en el nodo actual
    if (raiz->izq == NULL || raiz->der == NULL) { // el nodo a eliminar es una hoja o
                                                  // tiene exactamente un hijo
      AVL_Nodo *sucesor = (raiz->izq == NULL )? raiz->der : raiz->izq;
      destr(raiz->dato);
      free(raiz);
      // caso que tenga un hijo, lo toma, borra el padrey devuelve el hijo
      // en la recursion se va a enlazar con el abuelo
      return sucesor; // no es necesario rebalancear en este caso pues
      // el padre no tendra hijos o tendra
    } else { // el nodo a eliminar tiene dos hijos
      // agarra el mas chico del subarbol derecho
      AVL_Nodo *menor = avl_nodo_menor(raiz->der);
      
      // Reemplazar el dato del nodo actual con el dato del sucesor in-order
      destr(raiz->dato); // Liberar el dato actual
      raiz->dato = menor->dato; // Copiar el dato del sucesor
      
      // Eliminar el sucesor in-order del subárbol derecho
      raiz->der = avl_nodo_eliminar(raiz->der, menor->dato, destr, comp);
    }
  }

  // Actualizar altura y rebalancear a medida que vuelve la recursion
  raiz->altura = 1 + avl_nodo_max_altura_hijos(raiz);
  return avl_nodo_rebalancear(raiz);
}
void avl_eliminar(AVL arbol, void* dato) {
  arbol->raiz = avl_nodo_eliminar(arbol->raiz, dato, arbol->destr, arbol->comp);
}