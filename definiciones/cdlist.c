#include "estructuras/cdlist.h"
#include <stdlib.h>

CDList cdlist_crear() { return NULL; }

void cdlist_destruir(CDList lista) {
  DNodo *nodo = lista;
  if (nodo == NULL) return;

  do {
    DNodo *nodo_a_liberar = nodo;
    nodo                  = nodo->sig;
    free(nodo_a_liberar);
  } while (nodo != lista);
}

CDList cdlist_agregar_inicio(CDList lista, int dato) {
  DNodo *nuevo_nodo = malloc(sizeof(DNodo));
  nuevo_nodo->dato  = dato;

  if (lista == NULL) {
    nuevo_nodo->sig = nuevo_nodo;
    nuevo_nodo->ant = nuevo_nodo;
    return nuevo_nodo;
  }
  nuevo_nodo->sig = lista;
  nuevo_nodo->ant = lista->ant;

  (lista->ant)->sig = nuevo_nodo; // Ojo con los parentesis putos Y el orden con
                                  // la línea de abajo ☠️
  lista->ant = nuevo_nodo;
  return nuevo_nodo;
}

void cdlist_recorrer(
    CDList lista, DlFuncionVisitante visit, DListOrdenDeRecorrido sentido
) {

  if (lista == NULL) return;

  if (sentido == DLIST_RECORRIDO_HACIA_ADELANTE) {
    DNodo *nodo = lista;
    do {
      visit(nodo->dato);
      nodo = nodo->sig;
    } while (nodo != lista);
  } else {
    DNodo *nodo = lista->ant;
    do {
      visit(nodo->dato);
      nodo = nodo->ant;
    } while (nodo != lista->ant);
  }
}