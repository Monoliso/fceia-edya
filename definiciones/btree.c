#include "estructuras/btree.h"
#include "estructuras/gqueue.h"
#include <assert.h>
#include <stdio.h> //
#include <stdlib.h>

BTree btree_crear() { return NULL; }

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

int btree_empty(BTree nodo) { return nodo == NULL; }

BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void btree_recorrer(
    BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante04 visit) {
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

void btree_recorrer_preorden(BTree arbol, FuncionVisitante04 funcion) {
  if (!btree_empty(arbol)) {
    funcion(arbol->dato);
    btree_recorrer_preorden(arbol->left, funcion);
    btree_recorrer_preorden(arbol->right, funcion);
  }
}

void btree_recorrer_inorden(BTree arbol, FuncionVisitante04 funcion) {
  if (!btree_empty(arbol)) {
    btree_recorrer_inorden(arbol->left, funcion);
    funcion(arbol->dato);
    btree_recorrer_inorden(arbol->right, funcion);
  }
}

void btree_recorrer_postorden(BTree arbol, FuncionVisitante04 funcion) {
  if (!btree_empty(arbol)) {
    btree_recorrer_preorden(arbol->left, funcion);
    btree_recorrer_preorden(arbol->right, funcion);
    funcion(arbol->dato);
  }
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

int btree_buscar(BTree arbol, int dato) {
  if (btree_empty(arbol)) return 0;
  return arbol->dato == dato ? 1
                             : (btree_buscar(arbol->left, dato) ||
                                btree_buscar(arbol->right, dato));
}

int btree_nnodos(BTree arbol) {
  if (btree_empty(arbol)) return 0;
  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

BTree btree_copiar(BTree arbolito) {
  if (btree_empty(arbolito)) return NULL;
  return btree_unir(
      arbolito->dato, btree_copiar(arbolito->left),
      btree_copiar(arbolito->right));
}

int max(int a, int b) { return a > b ? a : b; }

int btree_altura(BTree arbol) {
  if (btree_empty(arbol)) return -1;
  return 1 + max(btree_altura(arbol->left), btree_altura(arbol->right));
}

int btree_nnodos_profundidad(BTree arbol, int profundidad) {
  if (btree_empty(arbol)) return 0;
  if (profundidad == 0) return 1;
  profundidad--;
  return btree_nnodos_profundidad(arbol->left, profundidad) +
         btree_nnodos_profundidad(arbol->right, profundidad);
}

int btree_profundidad(BTree arbol, int dato) {
  if (btree_empty(arbol)) return -1;
  if (arbol->dato == dato) return 0;
  int resultado =
      max(btree_profundidad(arbol->left, dato),
          btree_profundidad(arbol->right, dato));
  return resultado == -1 ? resultado : (++resultado);
}

int btree_sumar(BTree arbol) {
  if (btree_empty(arbol)) return 0;
  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
}

void btree_recorrer_extra(
    BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra04 visit,
    void *extra) {
  if (btree_empty(arbol) ||
      (btree_empty(arbol->left) && btree_empty(arbol->right)))
    return;
  switch (orden) {
  case BTREE_RECORRIDO_IN:
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
    break;
  case BTREE_RECORRIDO_PRE:
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
    break;
  case BTREE_RECORRIDO_POST:
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
    visit(arbol->dato, extra);
    break;
  }
  return;
}

void suma(int dato, int *resultado) { (*resultado) = dato + (*resultado); }

int btree_sumar_extra(BTree arbol) {
  int resultado = 0;
  btree_recorrer_extra(
      arbol, BTREE_RECORRIDO_IN, (FuncionVisitanteExtra04)suma, &resultado);
  return resultado;
}

// void aumentar(int dato, int *resultado) { (*resultado)++; }

// int btree_nnodos(BTree arbol) {
//   int resultado = 0;
//   btree_recorrer_extra(
//       arbol, BTREE_RECORRIDO_IN, (FuncionVisitanteExtra04)aumentar,
//       &resultado);
//   return resultado;
// }

void son_iguales(int dato, int *aparecio) {
  static int cosa;
  static int cargada = 0;
  if (!cargada) {
    cosa = dato;
    cargada = 1;
  }
  if (*aparecio) return;
  (*aparecio) = dato == cosa;
}

int btree_buscar_extra(BTree arbol, int cosa) {
  int resultado;
  son_iguales(cosa, &resultado);
  resultado = 0;
  btree_recorrer_extra(
      arbol, BTREE_RECORRIDO_IN, (FuncionVisitanteExtra04)son_iguales,
      &resultado);
  return resultado;
}

// BOOM

void btree_recorrer_bfs(
    BTree arbol, FuncionVisitante04 visit, FuncionCopia04 copia,
    FuncionDestructora04 demoledora) {
  int nodos = 0;
  int cant_nivel = 1;
  GQueue cola = gqueue_crear();
  cola = gqueue_encolar(cola, arbol, (FuncionCopia04)copia);

  printf("El árbol se mostrará bien si está completo.\n");
  while (!gqueue_vacia(cola)) {
    arbol = gqueue_inicio(cola, (FuncionCopia04)copia);
    cola = gqueue_desencolar(cola, (FuncionDestructora04)demoledora);
    if (!btree_empty(arbol->left)) {
      cola = gqueue_encolar(cola, arbol->left, (FuncionCopia04)copia);
    }
    if (!btree_empty(arbol->right)) {
      cola = gqueue_encolar(cola, arbol->right, (FuncionCopia04)copia);
    }
    visit(arbol->dato);
    nodos++;
    if (cant_nivel == nodos) {
      printf("\n");
      nodos = 0;
      cant_nivel *= 2;
    }
  }
  printf("\n");
  gqueue_destruir(cola, (FuncionDestructora04)demoledora);
}