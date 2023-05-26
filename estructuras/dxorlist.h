#ifndef __DLIST_H__
#define __DLIST_H__

typedef struct _DNodo {
  int dato;
  struct _DNodo *mascara;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
} DList;

typedef enum {
  DLIST_RECORRIDO_HACIA_ADELANTE,
  DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

typedef void (*FuncionVisitante)(int dato);

DList dlist_crear();

DList dlist_destruir(DList);

DList dlist_agregar_inicio(DList lista, int dato);

DList dlist_agregar_final(DList lista, int dato);

void dlist_recorrer(
    DList lista, FuncionVisitante visit, DListOrdenDeRecorrido sentido
);

#endif