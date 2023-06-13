#include "02-contacto.h"
#include "estructuras/arregloenteros.h"
#include "estructuras/glist.h"
#include "estructuras/gqueue.h"
#include "estructuras/gstack.h"
#include <stdio.h>
#include <stdlib.h>

int *copiar_int(int *entero) {
  int *copia = malloc(sizeof(int));
  *copia = *entero;
  return copia;
}

void eliminar_int(int *entero) { free(entero); };

void imprimir_int(int *entero) { printf("%d ", *entero); }

void ejercicio_02(Contacto **contactos) {
  // Pila pila00 = gstack_crear();
  Pila pila01 = gstack_crear();

  gstack_push01(&pila01, contactos[0], (FuncionCopia)contacto_copia);
  gstack_push01(&pila01, contactos[1], (FuncionCopia)contacto_copia);
  gstack_push01(&pila01, contactos[2], (FuncionCopia)contacto_copia);

  void *contacto_01 = gstack_pop(&pila01);
  void *contacto_02 = gstack_pop(&pila01);

  contacto_imprimir(contacto_01);
  contacto_imprimir(contacto_02);

  gstack_recorrer(pila01, (FuncionVisitante)contacto_imprimir);
  gstack_destruir(pila01, (FuncionDestructora)contacto_destruir);
  contacto_destruir(contacto_01);
  contacto_destruir(contacto_02);
}

void ejercicio_03(Contacto **contactos) {
  GList lista = glist_crear();
  Pila pila = gstack_crear();
  GList lista_invertida = glist_crear();

  for (int i = 0; i < 3; ++i) {
    lista =
        glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
  }

  for (GNode *nodo = lista; nodo != NULL; nodo = nodo->next) {
    gstack_push01(&pila, nodo->data, (FuncionCopia)contacto_copia);
  }

  int tamanio = gstack_tamanio(pila);
  for (int i = 0; i < tamanio; i++) {
    // En este for se recorre lo que se está quitando, no tiene sentido.
    // Lo que debe hacer es iterar el tamaño de la pila, popeando en cada
    // repetición.
    Contacto *contacto = gstack_pop(&pila);
    lista_invertida = glist_agregar_final(
        lista_invertida, contacto, (FuncionCopia)contacto_copia);
    contacto_destruir(contacto);
  }
  printf("\nLista normal\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  printf("\nLista invertida\n");
  glist_recorrer(lista_invertida, (FuncionVisitante)contacto_imprimir);
  glist_destruir(lista, (FuncionDestructora)contacto_destruir);
  glist_destruir(lista_invertida, (FuncionDestructora)contacto_destruir);
}

void ejercicio_04() {
  GQueue cola = gqueue_crear();
  printf("La cola está vacía: %d\n", gqueue_vacia(cola));

  for (int i = 0; i < 10; i++) {
    cola = gqueue_encolar(cola, &i, (FuncionCopia)copiar_int);
  }

  int *numero00 = gqueue_inicio(cola, (FuncionCopia)copiar_int);
  cola = gqueue_desencolar(cola, (FuncionDestructora)eliminar_int);
  int *numero01 = gqueue_inicio(cola, (FuncionCopia)copiar_int);
  printf("Números: %d y %d\n", *numero00, *numero01);
  eliminar_int(numero00);
  eliminar_int(numero01);

  cola = gqueue_desencolar(cola, (FuncionDestructora)eliminar_int);
  gqueue_imprimir(cola, (FuncionVisitante)imprimir_int);
  puts("");
  gqueue_destruir(cola, (FuncionDestructora)eliminar_int);
}

int main() {

  Contacto *contactos[3];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);

  // ejercicio_02(contactos);
  // ejercicio_03(contactos);
  ejercicio_04();

  contacto_destruir(contactos[0]);
  contacto_destruir(contactos[1]);
  contacto_destruir(contactos[2]);

  return 0;
}

// pila
// push(pila, dato)
// p b->b->N
// b-p>b->b->N
// dato = pop(pila)

// lista
// agregar_inicio(lista, dato)
