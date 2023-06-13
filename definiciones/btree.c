#include "estructuras/btree.h"
#include <assert.h>
#include <stdio.h> //
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
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(
    BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {
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

int cmp_int(int *a, int *b) { return *a - *b; }

void eliminar_int(int *entero) { free(entero); };

int *copiar_int(int *entero) {
  int *copia = malloc(sizeof(int));
  *copia = *entero;
  return copia;
}

void imprimir_linea(
    int dato, int izq, int *niveles_abiertos, int niv_recorridos) {
  // El problema con la pila es que tiene sentido para el guardado, pero a la
  // hora de imprimir cada línea tengo que saber cuales niveles siguen abiertos,
  // empezando por el primero, entonces cómo hago? Tengo una variable llamada
  // niveles recorridos?
  for (int i = 0; i < niv_recorridos; i++) {
    if (niveles_abiertos[i]) {
      printf("│  ");
    } else
      printf("   ");
  }
  if (dato != 0) {
    if (izq)
      printf("└─ %d\n", dato);
    else
      printf("│─ %d\n", dato);
  } else {
    if (izq)
      printf("└─ (nil)\n");
    else
      printf("│─ (nil)\n");
  }
}

void btree_imprimir_aux(
    BTree arbol, int izq, int *niv_abiertos, int niv_recorridos) {

  imprimir_linea(arbol->dato, izq, niv_abiertos, niv_recorridos);
  if (btree_empty(arbol->left) && btree_empty(arbol->right)) return;

  niv_recorridos++;
  niv_abiertos[niv_recorridos] = 1;

  if (btree_empty(arbol->left)) {
    btree_imprimir_aux(arbol->right, 0, niv_abiertos, niv_recorridos);
    imprimir_linea(0, 1, niv_abiertos, niv_recorridos);
  } else if (btree_empty(arbol->right)) {
    imprimir_linea(0, 0, niv_abiertos, niv_recorridos);
    niv_abiertos[niv_recorridos] = 0;
    btree_imprimir_aux(arbol->left, 1, niv_abiertos, niv_recorridos);
  } else {
    btree_imprimir_aux(arbol->right, 0, niv_abiertos, niv_recorridos);
    niv_abiertos[niv_recorridos] = 0;
    btree_imprimir_aux(arbol->left, 1, niv_abiertos, niv_recorridos);
  }
}

void btree_imprimir(BTree arbol) {
  if (btree_empty(arbol)) return;
  printf("%d\n", arbol->dato);
  int *niveles_abiertos = malloc(sizeof(int) * 50);
  int niv_recorridos = 0;
  niveles_abiertos[0] = 1;
  btree_imprimir_aux(arbol->right, 0, niveles_abiertos, niv_recorridos);
  niveles_abiertos[0] = 0;
  btree_imprimir_aux(arbol->left, 1, niveles_abiertos, niv_recorridos);
  free(niveles_abiertos);
}

/*
4
|- 3
|  |- 4
|  └ (nil)
└- 2
   |- (nil)
   └- 1
*/

/*
 5
 |- 4
 |  |- 2
 |  └- 3
 |     |- 5
 |     |  |- 8
 |     |  |  |- 10
 |     |  |  └- 11
 |     |  |      |- 12
 |     |  |      └- 13
 |     |  └- 9
 |     └- 6
 |        |- 1
 |        └- (nil)
 └- 3
    |- 0
    └- 2
 */