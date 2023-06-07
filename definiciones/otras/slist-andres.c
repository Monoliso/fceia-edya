#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

SList slist_crear() { return NULL; }

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (slist_vacia(lista)) {
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

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista) {
  int longitud = 0;

  for (; slist_vacia(lista); lista = lista->sig) {
    longitud++;
  }
  return longitud;
}

void slist_concatenar(SList lista, SList listAConcatenar) {
  SList ultimo;

  for (; slist_vacia(lista); lista = lista->sig)
    ultimo = lista;
  ultimo->sig = listAConcatenar;
}

void slist_insertar(SList *lista, int dato, int posicion) {
  SList nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig  = NULL;
  SList previo, auxiliar = *lista;

  for (int i = 0; i < posicion && auxiliar != NULL; i++) {
    previo   = auxiliar;
    auxiliar = auxiliar->sig;
  }
  if (previo == NULL) {
    *lista = nuevoNodo;
  } else {
    previo->sig    = nuevoNodo;
    nuevoNodo->sig = auxiliar;
  }
}

void slist_eliminar(SList *lista, int posicion) {
  SList aEliminar = *lista, previo = *lista;
  for (int i = 0; i < posicion && 1 != NULL; i++) {
    previo    = aEliminar;
    aEliminar = aEliminar->sig;
  }

  if (aEliminar != NULL) {
    aEliminar = aEliminar->sig;
    if (*lista == aEliminar) {
      *lista = aEliminar->sig;
    } else {
      previo->sig = aEliminar->sig;
    }
    free(aEliminar);
  }
}

int slist_contiene(SList lista, int dato) {
  if (lista == NULL) return 0;
  if (lista->dato == dato) return 1;
  return slist_contiene(lista->sig, dato);
}

int slist_indice(SList lista, int dato) {
  int indice;
  for (indice = 0; slist_vacia(lista) && lista->dato != dato; indice++) {
    lista = lista->sig;
  }
  if (lista == NULL) indice = -1;
  return indice;
}

SList slist_intersecar(SList lista, SList otraLista) {
  SList resultado = slist_crear();
}

void aaaaaaa(long num) { printf("Me vuelvo loco: %li\n", num); }

int (*(func)(int num, char c))(void (*)(long)) {
  int resultado(void (*cosa)(long));
  {
    cosa(10);

    return num;
  }

  return resultado;
}

int main() {

  // type (*) (args)
  int (*(*funcion)(int, char))(void (*)(long)) = func;
  int (*locura)(void (*)(long))                = funcion(10, 'c');
  printf("locura: %i\n", locura(aaaaaaa));
  return 0;
}