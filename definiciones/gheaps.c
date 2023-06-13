#include "estructuras/gheaps.h"
#include <stdio.h>
#include <stdlib.h>

BHeap bheap_crear(int capacidad, FuncionComparadora comparadora) {
  BHeap bheap      = malloc(sizeof(struct _BHeap));
  bheap->arr       = malloc(sizeof(void *) * (capacidad + 1));
  bheap->capacidad = capacidad;
  bheap->ultimo    = 0;
  bheap->comp      = comparadora;
  return bheap;
}

int bheap_vacio(BHeap bheap) { return bheap == NULL || bheap->ultimo == 0; }

BHeap bheap_insertar(BHeap bheap, void *dato, FuncionCopia copiar) {
  if (bheap == NULL) return NULL;
  if (bheap->capacidad == bheap->ultimo) {
    bheap->capacidad *= 2;
    bheap->arr = realloc(bheap->arr, sizeof(void *) * (bheap->capacidad + 1));
  }

  bheap->ultimo += 1;
  bheap->arr[bheap->ultimo] = copiar(dato);

  void **arreglo = bheap->arr;
  for (int pos = bheap->ultimo;
       pos > 1 && bheap->comp(arreglo[pos], arreglo[pos / 2]) > 0; pos /= 2) {
    void *temp       = arreglo[pos / 2];
    arreglo[pos / 2] = arreglo[pos];
    arreglo[pos]     = temp;
  }
  return bheap;
}

void bheap_destruir(BHeap bheap, FuncionDestructora demoledora) {
  for (int i = 1; i <= bheap->ultimo; i++)
    demoledora(bheap->arr[i]);
  free(bheap->arr);
  free(bheap);
}

BHeap bheap_eliminar(
    BHeap bheap, void *dato, FuncionComparadora comp,
    FuncionDestructora demoledora) {
  void **arreglo = bheap->arr;
  int i          = bheap->ultimo;
  for (; i > 1 && comp(dato, arreglo[i / 2]) > 0; i /= 2)
    ;
  // for (int i = 0; ) // Cómo puedo hacer que recorra un nivel, solo uno?
  return 0;
}