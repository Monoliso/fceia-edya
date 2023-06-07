#ifndef __CDLIST_H__
#define __CDLIST_H__

#include "dlist.h"

// typedef struct _DNodo {
//   int dato;
//   struct _DNodo *sig;
//   struct _DNodo *ant;
// } DNodo;

typedef DNodo *CDList;

// typedef enum {
//   DLIST_RECORRIDO_HACIA_ADELANTE,
//   DLIST_RECORRIDO_HACIA_ATRAS
// } DListOrdenDeRecorrido;

// typedef void (*FuncionVisitante)(int dato);

CDList cdlist_crear();

void cdlist_destruir(CDList);

CDList cdlist_agregar_inicio(CDList lista, int dato);

void cdlist_recorrer(
    CDList lista, DlFuncionVisitante visit, DListOrdenDeRecorrido sentido
);

#endif
