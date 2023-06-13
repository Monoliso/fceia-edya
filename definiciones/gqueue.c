#include "estructuras/gqueue.h"
#include "estructuras/glist.h"
#include <stdlib.h>

GQueue gqueue_crear() {
  GQueue cola = malloc(sizeof(_GQueue));
  cola->inicio = NULL;
  cola->final = NULL;
  return cola;
}

// Si la lista enlazada fuera una estructura con el nodo al inicio Y al final se
// podría hacer con un supuesto método que te devolviese el nodo al final,
// devolviendo el nodo agregado.
// cola->final = glist_agregar_final(cola->final, dato, copiar);
GQueue gqueue_encolar(GQueue cola, void *dato, FuncionCopia copiar) {
  GNode *nodo = malloc(sizeof(GNode));
  nodo->data = copiar(dato);
  nodo->next = NULL;

  if (cola->inicio == NULL) cola->inicio = nodo;
  if (cola->final != NULL) cola->final->next = nodo;
  cola->final = nodo;
  return cola;
}

GQueue gqueue_desencolar(GQueue cola, FuncionDestructora demoledora) {
  cola->inicio = glist_remover_inicio(cola->inicio, demoledora);
  if (cola->inicio == NULL) cola->final = NULL;
  return cola;
}

void *gqueue_inicio(GQueue cola, FuncionCopia copiar) {
  if (glist_vacia(cola->inicio)) return NULL;
  void *dato = copiar(cola->inicio->data);
  return dato;
}

int gqueue_vacia(GQueue cola) { return (cola == NULL || cola->inicio == NULL); }

void gqueue_destruir(GQueue cola, FuncionDestructora demoledora) {
  glist_destruir(cola->inicio, demoledora);
  cola->inicio = NULL;
  cola->final = NULL;
  free(cola);
}

void gqueue_imprimir(GQueue cola, FuncionVisitante visitante) {
  if (glist_vacia(cola->inicio)) return;
  for (GNode *nodo = cola->inicio; nodo != NULL; nodo = nodo->next)
    visitante(nodo->data);
}