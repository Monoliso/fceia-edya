#include "estructuras/slist.h"
#include <stdlib.h>

SList slist_crear() { return NULL; }

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista         = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) { return lista == NULL; }

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato  = dato;
  nuevoNodo->sig   = NULL;

  if (lista == NULL) return nuevoNodo;

  SList nodo = lista;
  for (; nodo->sig != NULL; nodo = nodo->sig)
    ;
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato  = dato;
  nuevoNodo->sig   = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, SlFuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

SList slist_arr(int *cadena, int largo) {
  SList lista = slist_crear();
  for (int i = largo - 1; i >= 0; i--) {
    lista = slist_agregar_inicio(lista, cadena[i]);
  }
  return lista;
}

SList slist_invertir(SList lista) {
  SList lista_invertida = slist_crear();
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig) {
    lista_invertida = slist_agregar_inicio(lista_invertida, nodo->dato);
  }
  return lista_invertida;
}