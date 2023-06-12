#ifndef GHEAPS_H
#define GHEAPS_H

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);

typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
  FuncionComparadora comp;
} *BHeap;

BHeap bheap_crear(int capacidad, FuncionComparadora comparadora);

BHeap bheap_insertar(BHeap bheap, void *dato, FuncionCopia copiar);

#endif