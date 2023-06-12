#include "glist.h"

#ifndef GSTACK_H
#define GSTACK_H

typedef GList Pila;

Pila gstack_crear();

Pila gstack_push00(Pila, void *dato, FuncionCopia);
void gstack_push01(Pila *, void *dato, FuncionCopia);

void *gstack_pop(Pila *);

// Como la idea de esta función es usarla en conjunción a desapilar para
// hacer el pop, entonces tiene que tener un método que copia el dato, así al
// desapilarlo en la siguiente función no se elimina. Esto es necesario
// porque los 2 métodos están separados.
/**
 * Retorna el elemento que se encuentre en el tope de la pila, pero sin
  eliminarlo.
*/
void *gstack_tope(Pila, FuncionCopia);

Pila gstack_desapilar00(Pila, FuncionDestructora);
void gstack_desapilar01(Pila *, FuncionDestructora);

void gstack_recorrer(Pila, FuncionVisitante);

void gstack_destruir(Pila, FuncionDestructora);

int gstack_vacia(Pila);

int gstack_tamanio(Pila);

#endif /* GSTACK_H */