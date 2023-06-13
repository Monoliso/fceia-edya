#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante04)(int dato);
typedef void (*FuncionVisitanteExtra04)(int dato, void *extra);
typedef void (*FuncionDestructora04)(void *dato);
typedef void *(*FuncionCopia04)(void *dato);
struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

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
void btree_recorrer(
    BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante04 visit);

void btree_recorrer_preorden(BTree arbol, FuncionVisitante04 funcion);
void btree_recorrer_inorden(BTree arbol, FuncionVisitante04 funcion);
void btree_recorrer_postorden(BTree arbol, FuncionVisitante04 funcion);

// ---------------------

/**
 * Imprime un esquema del árbol.
 */
void btree_imprimir(BTree arbol);

/**
 * Retorna el número de nodos del ́arbol.
 */
int btree_nnodos(BTree);

/**
 * Retorna 1 si el número dado se encuentra en el  ́arbol, y 0 en caso contrario.
 */
int btree_buscar(BTree, int);

/**
 * Retorna un nuevo ́arbol que sea una copia del ́arbol dado.
 */
BTree btree_copiar(BTree);

/**
 * Retorna la altura del ́arbol.
 */
int btree_altura(BTree);

/**
 * Retorna el número de nodos que se encuentran a la profundidad dada.
 */
int btree_nnodos_profundidad(BTree, int);

/**
 * Retorne la profundidad del nodo que contiene el número dado, y -1 si el
 * número no se encuentra en el árbol.
 */
int btree_profundidad(BTree arbol, int dato);

/**
 * Retorna la suma total de los datos del árbol.
 */
int btree_sumar(BTree);

void btree_recorrer_extra(
    BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra04 visit,
    void *extra);

int btree_sumar_extra(BTree);

int btree_buscar_extra(BTree, int);

void son_iguales(int, int *);

// Ejercicio 5
void btree_recorrer_bfs(
    BTree arbol, FuncionVisitante04 visit, FuncionCopia04 copia,
    FuncionDestructora04 demoledora);

#endif /* __BTREE_H__ */
