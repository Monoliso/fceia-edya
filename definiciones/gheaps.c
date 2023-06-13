#include "estructuras/gheaps.h"
#include <stdio.h>
#include <stdlib.h>

BHeap bheap_crear(int capacidad, FuncionComparadora comparadora) {
  BHeap bheap = malloc(sizeof(struct _BHeap));
  bheap->arr = malloc(sizeof(void *) * (capacidad + 1));
  bheap->capacidad = capacidad;
  bheap->ultimo = 0;
  bheap->comp = comparadora;
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
    void *temp = arreglo[pos / 2];
    arreglo[pos / 2] = arreglo[pos];
    arreglo[pos] = temp;
  }
  return bheap;
}

void bheap_destruir(BHeap bheap, FuncionDestructora demoledora) {
  for (int i = 1; i <= bheap->ultimo; i++)
    demoledora(bheap->arr[i]);
  free(bheap->arr);
  free(bheap);
}

BHeap bheap_eliminar(BHeap bheap, void *dato, FuncionDestructora demoledora) {
  int pos_padre = 1;
  int sea_mayor = 0;
  void **arreglo = bheap->arr;
  // bheap->arr[i] != dato
  for (;
       bheap->comp(arreglo[pos_padre], dato) != 0 && pos_padre <= bheap->ultimo;
       pos_padre++)
    ;
  if (pos_padre > bheap->ultimo) return bheap;

  demoledora(arreglo[pos_padre]);
  bheap->ultimo -= 1;

  while (pos_padre * 2 < bheap->ultimo && !sea_mayor) {
    int pos_hijo = pos_padre * 2;
    // arreglo[pos_hijo + 1] > arreglo[pos_hijo]
    if (pos_hijo + 1 <= bheap->ultimo &&
        bheap->comp(arreglo[pos_hijo + 1], arreglo[pos_hijo]) > 0) {
      pos_hijo += 1;
    }
    // arreglo[i] > arreglo[pos_hijo]
    if (bheap->comp(arreglo[pos_padre], arreglo[pos_hijo]) > 0)
      sea_mayor = 1;
    else {
      void *temp = arreglo[pos_padre];
      arreglo[pos_padre] = arreglo[pos_hijo];
      arreglo[pos_hijo] = temp;
    }
    pos_padre = pos_hijo;
  }
  return bheap;
}