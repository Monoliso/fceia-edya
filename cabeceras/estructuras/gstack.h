#include "glist.h"

#ifndef GSTACK_H
#define GSTACK_H

typedef GList Pila;

Pila gstack_crear();

Pila gstack_push(Pila, void *dato, FuncionCopia);

Pila gstack_pop(Pila, FuncionVisitante, FuncionDestructora);

void gstack_recorrer(Pila, FuncionVisitante);

void gstack_destruir(Pila, FuncionDestructora);

int gstack_vacia(Pila);

#endif /* GSTACK_H */