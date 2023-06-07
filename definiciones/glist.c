#include "estructuras/glist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list         = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

GList glist_remover_inicio(GList lista, FuncionDestructora demoledora) {
  if (glist_vacia(lista)) return NULL;

  GNode *nueva_lista = lista->next;
  lista->next        = NULL;
  glist_destruir(lista, demoledora);
  return nueva_lista;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

/**
 * Devuelve una lista que cumpla con las condiciones p.
 */
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p) {
  GList nueva_lista = glist_crear();

  if (lista == NULL) return NULL;

  for (GNode *nodo = lista; nodo != NULL; nodo = nodo->next) {
    if (p(nodo->data)) {
      nueva_lista = glist_agregar_inicio(nueva_lista, nodo->data, c);
    }
  }
  return nueva_lista;
}

// --------------------------

SGList sglist_crear() { return NULL; }

void sglist_destruir(SGList lista, FuncionDestructora demoledora) {
  GNode *nodeToDelete;
  while (lista != NULL) {
    nodeToDelete = lista;
    lista        = lista->next;
    demoledora(nodeToDelete->data);
    // printf("Borrado %p\n", nodeToDelete);
    free(nodeToDelete);
  }
}

int sglist_vacia(SGList lista) { return (lista == NULL); }

void sglist_recorrer(SGList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
};

SGList sglist_insertar(
    SGList lista, void *dato, FuncionCopia copiar, FuncionComparadora comparar
) {
  GNode *nuevo_nodo = malloc(sizeof(GNode));
  nuevo_nodo->data  = copiar(dato);

  int insertado        = 0;
  GNode *nodo          = lista;
  GNode *nodo_anterior = NULL;

  // 3er Intento
  // while (insertado != 1) {
  //   if (nodo != NULL && comparar(nodo->data, dato) < 0) {
  //     nodo_anterior = nodo;
  //     nodo          = nodo->next;
  //   } else {
  //     if (nodo_anterior != NULL) {
  //       nuevo_nodo->next    = nodo;
  //       nodo_anterior->next = nuevo_nodo;
  //     } else {
  //       nuevo_nodo->next = NULL;
  //     }
  //     nodo_anterior = nodo;
  //     insertado     = 1;
  //   }
  // }

  while (insertado != 1) {
    if (nodo != NULL && comparar(nodo->data, dato) < 0) {
      nodo_anterior = nodo;
      nodo          = nodo->next;
    } else {
      if (nodo_anterior != NULL) nodo_anterior->next = nuevo_nodo;
      if (nodo == NULL)
        nuevo_nodo->next = NULL;
      else
        nuevo_nodo->next = nodo;

      insertado = 1;
    }
  }
  return (nuevo_nodo->next == lista) ? nuevo_nodo : lista;
}

int sglist_buscar(SGList lista, void *dato, FuncionComparadora comparar) {
  int encontrado = 0, buscar = 1;
  GNode *nodo = lista;
  for (; encontrado != 1 && buscar == 1 && nodo != NULL; nodo = nodo->next) {
    if (nodo == NULL) buscar = 0;
    if (comparar(nodo->data, dato) == 0) {
      encontrado = 1;
      buscar     = 0;
    }
  }
  return encontrado;
}

SGList sglist_arr(
    void **arreglo, int longitud, FuncionCopia copiar,
    FuncionComparadora comparar
) {
  SGList lista = sglist_crear();
  if (arreglo == NULL) return NULL;
  for (int i = 0; i < longitud; i++) {
    lista = sglist_insertar(lista, arreglo[i], copiar, comparar);
  }
  return lista;
}