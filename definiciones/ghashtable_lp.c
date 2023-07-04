#include "estructuras/ghashtable.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define LIM_FACTOR_CARGA 0.5

typedef struct {
  void *dato;
} CasillaHash;

struct _TablaHash {
  CasillaHash **elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

TablaHash ghashtable_crear(
    unsigned capacidad, FuncionCopiadora copia, FuncionComparadora comp,
    FuncionDestructora destr, FuncionHash hash) {

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
  tabla->hash = hash;
  return tabla;
}

// La definición original es una mierda, como uno siempre uno termina realizando
// el módulo no entiendo por qué lo define con la recursión. Excepto que esté
// terriblemente equivocado, esta definición computa lo mismo y cicla siempre
// alrededor de la capacidad.
unsigned k_hasheo(TablaHash tabla, void *dato, int k) {
  return (tabla->hash(dato) + k) % tabla->capacidad;
}

unsigned hashear(TablaHash tabla, void *dato) {
  return k_hasheo(tabla, dato, 0);
}

unsigned int ghashtable_nelems(TablaHash tabla) { return tabla->numElems; }

unsigned int ghashtable_capacidad(TablaHash tabla) { return tabla->capacidad; }

static bool casillahash_vacia(CasillaHash *casilla) {
  if (casilla) return casilla->dato ? false : true;
  return true;
}

void ghashtable_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    CasillaHash *casilla = tabla->elems[idx];
    if (casilla) {
      if (casilla->dato) tabla->destr(casilla->dato);
      free(tabla->elems[idx]);
    }
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

void ghashtable_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned i = hashear(tabla, dato);
  void *nuevo_dato = tabla->copia(dato);
  float factor_carga = (float)(tabla->numElems + 1) / (float)tabla->capacidad;
  if (factor_carga > LIM_FACTOR_CARGA) ghashtable_redimensionar(tabla);
  // Asumimos que nunca que se va a quedar sin espacio

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[i] == NULL) {
    tabla->numElems++;
    tabla->elems[i] = malloc(sizeof(CasillaHash));
    tabla->elems[i]->dato = nuevo_dato;
    return;
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  if (tabla->comp(tabla->elems[i]->dato, dato) == 0) {
    tabla->destr(tabla->elems[i]->dato);
    tabla->elems[i]->dato = nuevo_dato;
    return;
  }
  // Realizar Linear Probing.
  bool condicion = true;
  tabla->numElems++;
  for (int k = 1; condicion; k++) {
    i = k_hasheo(tabla, dato, k);
    if (casillahash_vacia(tabla->elems[i])) {
      if (!tabla->elems[i]) tabla->elems[i] = malloc(sizeof(CasillaHash));
      tabla->elems[i]->dato = nuevo_dato;
      condicion = false;
    }
  }
  return;
}

void *ghashtable_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned i = hashear(tabla, dato);
  CasillaHash *casilla = tabla->elems[i];

  // Retornar NULL si la casilla estaba vacia.
  if (casillahash_vacia(casilla)) return NULL;
  // Retornar el dato de la casilla si hay concidencia.
  if (tabla->comp(casilla->dato, dato) == 0) return casilla->dato;
  // Continuar buscando con los siguiente.
  bool condicion = true;
  for (int k = 1; condicion && k < (int)tabla->capacidad; k++) {
    i = k_hasheo(tabla, dato, k);
    casilla = tabla->elems[i];
    if (!casillahash_vacia(casilla) && tabla->comp(casilla->dato, dato) == 0)
      condicion = false;
  }
  return condicion ? NULL : casilla->dato;
}

void ghashtable_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned i = hashear(tabla, dato);
  CasillaHash *casilla = tabla->elems[i];

  // Retornar si la casilla estaba vacia.
  if (!casilla) return;

  // Si no hay coincidencias seguir buscando adelante.
  bool condicion = true;
  for (int k = 1; condicion; k++) {
    i = k_hasheo(tabla, dato, k);
    casilla = tabla->elems[i];
    if (!casillahash_vacia(casilla) && tabla->comp(casilla->dato, dato) == 0) {
      tabla->numElems--;
      tabla->destr(casilla->dato);
      casilla->dato = NULL;
      condicion = false;
    }
  }
}

void ghashtable_redimensionar(TablaHash tabla) {
  CasillaHash **elementos = tabla->elems;
  unsigned vieja_capacidad = tabla->capacidad;
  tabla->capacidad *= 2;
  tabla->elems = calloc(tabla->capacidad, sizeof(CasillaHash *));

  for (unsigned int i = 0; i < vieja_capacidad; i++) {
    CasillaHash *casilla = elementos[i];
    if (!casillahash_vacia(casilla)) {
      unsigned i = hashear(tabla, casilla->dato);
      tabla->elems[i] = casilla;
    }
  }
  free(elementos);
}