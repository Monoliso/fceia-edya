#include "estructuras/gbstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Implementacion alternativa para arboles de busqueda binaria.
 * Se mantienen dos niveles de abstraccion:
 * El nivel inferior implementa ABB con datos de tipo void*.
 * El nivel superior encapsula el ABB y las funciones que copian,
 * destruyen y comparan los datos.
 * El nivel superior es con quien se comunica el usuario y se encarga de
 * llamar a las funciones del nivel inferior con los parametros apropiados.
 */

/**
 * Nivel inferior:
 * ===============
 */

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
typedef struct _GBT_Nodo {
  void *dato;
  struct _GBT_Nodo *izq, *der;
} GBT_Nodo;

typedef GBT_Nodo BST_Nodo;

/**
 * A continuacion, se implementan las funciones del nivel inferior.
 * Las mismas se declaran como static, es decir, solo pueden ser llamadas desde
 * este modulo. De esta forma, se impide al usuario llamarlas directamente, sin
 * pasar por el nivel superior.
 */

static void bstree_nodo_destruir(BST_Nodo *raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_nodo_destruir(raiz->izq, destr);
    bstree_nodo_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};

static int
bstree_nodo_buscar(BST_Nodo *raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return bstree_nodo_buscar(raiz->izq, dato, comp);
  else // raiz->dato < dato
    return bstree_nodo_buscar(raiz->der, dato, comp);
}

static BST_Nodo *bstree_nodo_insertar(
    BST_Nodo *raiz, void *dato, FuncionCopiadora copia,
    FuncionComparadora comp) {
  if (raiz == NULL) { // insertar el dato en un nuevo nodo
    BST_Nodo *nuevoNodo = malloc(sizeof(struct _GBT_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    raiz->izq = bstree_nodo_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
    raiz->der = bstree_nodo_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

static void bstree_nodo_recorrer(
    BST_Nodo *raiz, BSTreeRecorrido orden, FuncionVisitanteExtra visita,
    void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE) visita(raiz->dato, extra);
    bstree_nodo_recorrer(raiz->izq, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_IN) visita(raiz->dato, extra);
    bstree_nodo_recorrer(raiz->der, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_POST) visita(raiz->dato, extra);
  }
}

/**
 * Nivel superior:
 * ===============
 */

/**
 * Estructura del arbol de busqueda binaria.
 * Tiene un puntero al nodo raiz (raiz),
 * un puntero a funcion (copia) que recibe un dato y retorna un puntero con la
 * direccion de memoria de una copia fisica del dato,
 * un puntero a funcion (comp) que compara dos datos y retorna un entero
 * negativo si el primero es menor que el segundo, 0 si son iguales, y un entero
 * positivo en caso contrario,
 * y un puntero a una funcion (destr) que recibe un dato y lo destruye.
 */
struct _BSTree {
  BST_Nodo *raiz;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionImpresora impresora;
};

/**
 * Retorna un arbol de busqueda binaria vacio.
 * Por unica vez se piden por parametro los punteros a funcion.
 */
BSTree bstee_crear(
    FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr,
    FuncionImpresora imprimir) {
  BSTree arbol = malloc(sizeof(struct _BSTree));
  assert(arbol != NULL);
  arbol->raiz = NULL;
  arbol->copia = copia;
  arbol->comp = comp;
  arbol->destr = destr;
  arbol->impresora = imprimir;
  return arbol;
}

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree arbol) {
  bstree_nodo_destruir(arbol->raiz, arbol->destr);
  free(arbol);
}

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree arbol, void *dato) {
  return bstree_nodo_buscar(arbol->raiz, dato, arbol->comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
void bstree_insertar(BSTree arbol, void *dato) {
  arbol->raiz =
      bstree_nodo_insertar(arbol->raiz, dato, arbol->copia, arbol->comp);
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(
    BSTree arbol, BSTreeRecorrido orden, FuncionVisitanteExtra visita,
    void *extra) {
  bstree_nodo_recorrer(arbol->raiz, orden, visita, extra);
}

// --------------------------
BSTree bts_crear_desde_preorden(
    void **preorden, int dimension, FuncionCopiadora copiar,
    FuncionComparadora comp, FuncionDestructora demoledora,
    FuncionImpresora imprimir) {
  if (!preorden || !dimension) return NULL;
  BSTree arbol = bstee_crear(copiar, comp, demoledora, imprimir);
  for (int i = 0; i < dimension; i++) {
    bstree_insertar(arbol, preorden[i]);
  }
  return arbol;
}

int gbtree_vacio(GBT_Nodo *arbol) { return arbol == NULL; }

int bstree_vacio(BSTree arbol) {
  return arbol == NULL || gbtree_vacio(arbol->raiz);
}

void bstree_imprimir_aux(
    BST_Nodo *arbol, int es_izq, int *niveles_abiertos, int num_niveles,
    FuncionImpresora impresora) {

  for (int i = 0; i < num_niveles; i++)
    printf("%s", niveles_abiertos[i] ? "│  " : "   ");
  printf("%s ", es_izq ? "└─" : "│─");

  if (gbtree_vacio(arbol)) {
    printf("(nil)\n");
    return;
  }
  impresora(arbol->dato);
  printf("\n");
  if (gbtree_vacio(arbol->izq) && gbtree_vacio(arbol->der)) return;

  num_niveles++;
  niveles_abiertos[num_niveles] = 1;
  bstree_imprimir_aux(arbol->der, 0, niveles_abiertos, num_niveles, impresora);
  niveles_abiertos[num_niveles] = 0;
  bstree_imprimir_aux(arbol->izq, 1, niveles_abiertos, num_niveles, impresora);
}

void bstree_imprimir(BSTree arbol) {
  if (bstree_vacio(arbol)) {
    printf("(nil)\n");
    return;
  };

  BST_Nodo *nodo = arbol->raiz;
  arbol->impresora(nodo->dato);
  printf("\n");
  int niveles_abiertos[50] = {1};
  bstree_imprimir_aux(nodo->der, 0, niveles_abiertos, 0, arbol->impresora);
  niveles_abiertos[0] = 0;
  bstree_imprimir_aux(nodo->izq, 1, niveles_abiertos, 0, arbol->impresora);
}