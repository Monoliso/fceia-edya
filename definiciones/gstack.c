#include "estructuras/gstack.h"
#include "estructuras/glist.h"
#include <stdlib.h>

Pila gstack_crear() { return glist_crear(); }

void gstack_push01(Pila *dir_pila, void *dato, FuncionCopia copiar) {
  *dir_pila = glist_agregar_inicio(*dir_pila, dato, copiar);
}

void *gstack_pop(Pila *dir_pila) {
  Pila pila = *dir_pila;
  if (gstack_vacia(pila)) return NULL;
  void *dato = pila->data;
  *dir_pila  = pila->next;
  free(pila);
  return dato;
}

void *gstack_tope(Pila pila, FuncionCopia copiar) {
  if (gstack_vacia(pila)) return NULL;
  return copiar(pila->data);
}

void gstack_desapilar01(Pila *dir_pila, FuncionDestructora demoledora) {
  Pila pila = *dir_pila;
  *dir_pila = glist_remover_inicio(pila, demoledora);
}

void gstack_recorrer(Pila pila, FuncionVisitante f) { glist_recorrer(pila, f); }

void gstack_destruir(Pila pila, FuncionDestructora demoledora) {
  if (gstack_vacia(pila)) return;
  glist_destruir(pila, demoledora);
}

int gstack_vacia(Pila pila) { return pila == NULL; }

int gstack_tamanio(Pila pila) {
  int contador = 0;
  if (gstack_vacia(pila)) return 0;
  for (GNode *nodo = pila; nodo != NULL; nodo = nodo->next)
    contador = contador + 1;
  return contador;
}