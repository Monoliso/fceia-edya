#include "glist.h"

#ifndef GQUEUE_H
#define GQUEUE_H

typedef struct {
  GNode *inicio;
  GNode *final;
} _GQueue;

typedef _GQueue *GQueue;

// GCola gqueue_crear();
GQueue gqueue_crear();

void gqueue_destruir(GQueue, FuncionDestructora);

int gqueue_vacia(GQueue);

void *gqueue_inicio(GQueue, FuncionCopia);

GQueue gqueue_encolar(GQueue, void *, FuncionCopia);

GQueue gqueue_desencolar(GQueue, FuncionDestructora);

void gqueue_imprimir(GQueue, FuncionVisitante);

#endif