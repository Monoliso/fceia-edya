#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef GList SGList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Elimina un elemento de la lista si se encuentra. La eficiencia depende de la
 * implementación.
 */
GList glist_remover_elemento(
    GList, FuncionDestructora, FuncionComparadora, void *);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

int glist_tamanio(GList);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, void *dato, FuncionCopia copiar);

GList glist_remover_inicio(GList, FuncionDestructora);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Devuelve una lista que cumpla con las condiciones p.
 */
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);

// --------------------------

SGList sglist_crear();

void sglist_destruir(SGList, FuncionDestructora);

int sglist_vacia(SGList);

void sglist_recorrer(SGList, FuncionVisitante);

SGList sglist_insertar(SGList, void *, FuncionCopia, FuncionComparadora);

int sglist_buscar(SGList, void *, FuncionComparadora);

SGList sglist_arr(void **, int, FuncionCopia, FuncionComparadora);

#endif /* __GLIST_H__ */
