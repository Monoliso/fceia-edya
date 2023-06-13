#include "estructuras/gheaps.h"
#include <stdio.h>
#include <stdlib.h>

int cmp_int(int *a, int *b) { return *a - *b; }

void eliminar_int(int *entero) { free(entero); };

int *copiar_int(int *entero) {
  int *copia = malloc(sizeof(int));
  *copia     = *entero;
  return copia;
}

int main() {
  BHeap bheap = bheap_crear(5, (FuncionComparadora)cmp_int);
  for (int i = 0; i < 5; i++) {
    bheap = bheap_insertar(bheap, &i, (FuncionCopia)copiar_int);
  }

  int **valor = (int **)bheap->arr;
  for (int i = 1; i <= 5; i++) {
    printf("%d ", *(valor[i]));
  }
  puts("");

  bheap_destruir(bheap, (FuncionDestructora)eliminar_int);
  return 0;
}