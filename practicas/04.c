#include "estructuras/btree.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(int data) { printf("%d ", data); }

void *id(void *dato) { return dato; }
void vacio(void *dato) { id(dato); }
int cmp_int(int *a, int *b) { return *a - *b; }

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, btree_unir(4, r, btree_crear()));

  BTree arbol = btree_unir(
      95,
      btree_unir(
          73,
          btree_unir(
              38, btree_unir(22, NULL, NULL), btree_unir(10, NULL, NULL)),
          btree_unir(
              60, btree_unir(52, NULL, NULL), btree_unir(15, NULL, NULL))),
      btree_unir(45, btree_unir(33, NULL, NULL), btree_unir(40, NULL, NULL)));

  printf("Recorrido en INORDEN: ");
  btree_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  printf("Esquema del árbol:\n");
  btree_imprimir(arbol);
  print_binary_tree(arbol);
  btree_recorrer_bfs(
      arbol, (FuncionVisitante04)imprimir_entero, (FuncionCopia04)id,
      (FuncionDestructora04)vacio);
  printf("La altura del árbol es: %d\n", btree_altura(arbol));
  printf(
      "La profundidad del nodo con el número 22 es: %d\n",
      btree_profundidad(arbol, 22));
  printf(
      "La cantidad de nodos en la altura 4 es: %d\n",
      btree_nnodos_profundidad(arbol, 4));

  btree_destruir(raiz);
  btree_destruir(arbol);

  return 0;
}
