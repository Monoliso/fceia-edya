#include "tablahash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define FAC_CARGA 0.75

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash **elems; // Cambio la definición para marcar como "eliminado"
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionImpresora imprimir;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(
    unsigned capacidad, FuncionCopiadora copia, FuncionComparadora comp,
    FuncionDestructora destr, FuncionImpresora imprimir, FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = calloc(capacidad, sizeof(CasillaHash *));
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->imprimir = imprimir;
  tabla->hash = hash;

  return tabla;
}

// -----------------------

void _tablahash_redimensionar(TablaHash);

int casilla_vacia(CasillaHash *casilla) {

  if (casilla) return casilla->dato ? 0 : 1;
  return 1;
}

void tablahash_imprimir(TablaHash tabla) {

  puts("--------------------");
  for (int i = 0; i < tabla->capacidad; i++) {
    if (!casilla_vacia(tabla->elems[i])) {
      tabla->imprimir(tabla->elems[i]->dato);
      puts("");
    } else if (tabla->elems[i])
      puts("Eliminado");
    else
      puts("Vacio");
    puts("--------------------");
  }
}

CasillaHash *_tablahash_buscar(TablaHash tabla, void *dato) {

  void *casilla_buscada = NULL;
  for (int i = 0, condicion = 0; !condicion && i < tabla->capacidad; i++) {
    unsigned idx = (tabla->hash(dato) + i) % tabla->capacidad;
    if (!tabla->elems[idx])
      condicion = 1; // Terminó el cluster
    else if (
        !casilla_vacia(tabla->elems[idx]) &&
        tabla->comp(tabla->elems[idx]->dato, dato) == 0) {
      casilla_buscada = tabla->elems[idx];
      condicion = 1;
    }
  }
  return casilla_buscada;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  CasillaHash *casilla = _tablahash_buscar(tabla, dato);
  if (casilla) return tabla->copia(casilla->dato);
  return NULL;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  if (!tabla) return;

  for (int i = 0; i < tabla->capacidad; i++) {
    if (tabla->elems[i]) {
      if (tabla->elems[i]->dato) tabla->destr(tabla->elems[i]->dato);
      free(tabla->elems[i]);
    }
  }
  free(tabla->elems);
  free(tabla);
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void _tablahash_insertar(TablaHash tabla, void *dato) {

  if (!tabla) return;

  float factor_carga = (float)(tabla->numElems + 1) / (float)tabla->capacidad;
  if (factor_carga >= FAC_CARGA) {
    _tablahash_redimensionar(tabla);
  }

  tabla->numElems++;
  for (int i = 0, condicion = 0; !condicion && i < tabla->capacidad; i++) {
    unsigned idx = (tabla->hash(dato) + i) % tabla->capacidad;
    if (casilla_vacia(tabla->elems[idx])) {
      if (!tabla->elems[idx]) tabla->elems[idx] = malloc(sizeof(CasillaHash));
      tabla->elems[idx]->dato = dato;
      condicion = 1;
    }
  }
}

void tablahash_insertar(TablaHash tabla, void *dato) {
  _tablahash_insertar(tabla, tabla->copia(dato));
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  CasillaHash *casilla = _tablahash_buscar(tabla, dato);
  if (casilla) {
    tabla->numElems--;
    tabla->destr(casilla->dato);
    casilla->dato = NULL;
  }
}

/*
 * Redimensiona la tabla al doble de su tamaño.
 */
void _tablahash_redimensionar(TablaHash tabla) {

  CasillaHash **viejos_elems = tabla->elems;
  unsigned numElems = tabla->numElems;
  tabla->capacidad *= 2;
  tabla->elems = calloc(tabla->capacidad, sizeof(CasillaHash *));
  tabla->numElems = 0;

  for (int i = 0, x = 0; x < numElems; i++) {
    if (viejos_elems[i]) {
      _tablahash_insertar(tabla, viejos_elems[i]->dato);
      free(viejos_elems[i]);
      x++;
    }
  }
  free(viejos_elems);
  return;
}

/**
 * Devuelve el tamaño del cluster primario más grande.
 */
int tablahash_max_cluster(TablaHash tabla) {

  int max_cluster = 0;
  int cluster_circular = 0;

  for (int i = 0, cluster_actual = 0; i < tabla->capacidad; i++) {
    if (tabla->elems[i]) {
      cluster_actual++;
      if (i == tabla->capacidad - 1) cluster_circular += cluster_actual;
      if (cluster_actual > max_cluster) max_cluster = cluster_actual;
    } else {
      if (tabla->elems[0] && !cluster_circular)
        cluster_circular += cluster_actual;
      cluster_actual = 0;
    }
  }
  // printf("%d", cluster_circular);
  return max_cluster > cluster_circular ? max_cluster : cluster_circular;
}