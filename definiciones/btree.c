#include "estructuras/btree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato  = dato;
  nuevoNodo->left  = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(
    BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit
) {
  /** COMPLETAR */
  if (btree_empty(arbol)) return;
  assert(!btree_empty(arbol));

  if (orden == BTREE_RECORRIDO_PRE)
    btree_recorrer_preorden(arbol, visit);
  else if (orden == BTREE_RECORRIDO_IN)
    btree_recorrer_inorden(arbol, visit);
  else
    btree_recorrer_postorden(arbol, visit);
  return;
}

void btree_recorrer_preorden(BTree arbol, FuncionVisitante funcion) {
  if (!btree_empty(arbol)) {
    funcion(arbol->dato);
    btree_recorrer_preorden(arbol->left, funcion);
    btree_recorrer_preorden(arbol->right, funcion);
  }
}

void btree_recorrer_inorden(BTree arbol, FuncionVisitante funcion) {
  if (!btree_empty(arbol)) {
    btree_recorrer_preorden(arbol->left, funcion);
    funcion(arbol->dato);
    btree_recorrer_preorden(arbol->right, funcion);
  }
}

void btree_recorrer_postorden(BTree arbol, FuncionVisitante funcion) {
  if (!btree_empty(arbol)) {
    btree_recorrer_preorden(arbol->left, funcion);
    btree_recorrer_preorden(arbol->right, funcion);
    funcion(arbol->dato);
  }
}