#include "estructuras/dlist.h"
#include <stdlib.h>

DList dlist_crear() {
  DList dlist = {NULL, NULL};
  return dlist;
}

DList dlist_destruir(DList lista) {
  DNodo *inicio = lista.primero;
  while (inicio != NULL) {
    DNodo *nodo_a_eliminar = inicio;
    inicio                 = inicio->sig;
    free(nodo_a_eliminar);
  }
  lista.primero = NULL;
  lista.ultimo  = NULL;
  return lista;
}

DList dlist_agregar_inicio(DList lista, int dato) {
  DNodo *primero_anterior = lista.primero;
  DNodo *nuevo_elemento   = malloc(sizeof(DNodo));
  nuevo_elemento->dato    = dato;
  nuevo_elemento->sig     = primero_anterior;
  nuevo_elemento->ant     = NULL;

  lista.primero = nuevo_elemento;
  if (primero_anterior != NULL)
    primero_anterior->ant = nuevo_elemento;
  else
    lista.ultimo = nuevo_elemento;
  return lista;
}

DList dlist_agregar_final(DList lista, int dato) {
  DNodo *ultimo_anterior = lista.ultimo;
  DNodo *nuevo_elemento  = malloc(sizeof(DNodo));
  nuevo_elemento->dato   = dato;
  nuevo_elemento->sig    = NULL;
  nuevo_elemento->ant    = ultimo_anterior;

  lista.ultimo = nuevo_elemento;
  if (ultimo_anterior != NULL)
    ultimo_anterior->sig = nuevo_elemento;
  else
    lista.primero = nuevo_elemento;
  return lista;
}

void dlist_recorrer(
    DList lista, DlFuncionVisitante visit, DListOrdenDeRecorrido sentido
) {

  if (sentido == DLIST_RECORRIDO_HACIA_ADELANTE) {
    DNodo *nodo = lista.primero;
    while (nodo != NULL) {
      visit(nodo->dato);
      nodo = nodo->sig;
    }

  } else {
    DNodo *nodo = lista.ultimo;
    while (nodo != NULL) {
      visit(nodo->dato);
      nodo = nodo->ant;
    }
  }
}