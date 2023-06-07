#include "estructuras/gstack.h"
#include <stdio.h>

Pila gstack_crear() { return glist_crear(); }

Pila gstack_push(Pila pila, void *dato, FuncionCopia copiar) {
  pila = glist_agregar_inicio(pila, dato, copiar);
  return pila;
}

Pila gstack_pop(Pila pila, FuncionVisitante f, FuncionDestructora demoledora) {
  if (gstack_vacia(pila)) return NULL;
  f(pila->data);
  return glist_remover_inicio(pila, demoledora);
}

void gstack_recorrer(Pila pila, FuncionVisitante f) { glist_recorrer(pila, f); }

void gstack_destruir(Pila pila, FuncionDestructora demoledora) {
  if (gstack_vacia(pila)) return;
  glist_destruir(pila, demoledora);
}

int gstack_vacia(Pila pila) { return pila == NULL; }