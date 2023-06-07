#include "02-contacto.h"
#include "estructuras/arregloenteros.h"
#include "estructuras/gstack.h"
#include <stdio.h>

int main() {
  Pila pila = gstack_crear();
  Contacto *contactos[2];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);

  pila = gstack_push(pila, contactos[0], (FuncionCopia)contacto_copia);
  pila = gstack_push(pila, contactos[1], (FuncionCopia)contacto_copia);
  pila = gstack_push(pila, contactos[0], (FuncionCopia)contacto_copia);

  pila = gstack_pop(
      pila, (FuncionVisitante)contacto_imprimir,
      (FuncionDestructora)contacto_destruir
  );
  pila = gstack_pop(
      pila, (FuncionVisitante)contacto_imprimir,
      (FuncionDestructora)contacto_destruir
  );

  gstack_recorrer(pila, (FuncionVisitante)contacto_imprimir);
  gstack_destruir(pila, (FuncionDestructora)contacto_destruir);
  contacto_destruir(contactos[0]);
  contacto_destruir(contactos[1]);
  return 0;
}