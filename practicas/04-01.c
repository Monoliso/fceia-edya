#include "estructuras/gbstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Casos de prueba para arboles de busqueda binaria generales
 */

#define N_PALABRAS 16

static void *copiar_cadena(void *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  assert(str != NULL);
  strcpy(str, dato);
  return str;
}
static int comparar_cadena(void *dato1, void *dato2) {
  return strcmp(dato1, dato2);
}
static void destruir_cadena(void *dato) { free(dato); }
static void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
  /* __attribute__((unused)) le dice al compilador que esta variable puede no
   * ser usada, de esta forma las banderas no tiran warnings.*/
  printf("\"%s\" ", (char *)dato);
}

void imprimir_entero(int *data) { printf("%d", *data); }
void imprimir_string(char *data) { printf("%s", data); }
void *id(void *dato) { return dato; }
void vacio(void *dato) { id(dato); }
int *copiar_int(int *entero) {
  int *copia = malloc(sizeof(int));
  *copia = *entero;
  return copia;
}
void eliminar_int(int *entero) { free(entero); };
int cmp_int(int *a, int *b) {
  int resultado = *a - *b;
  return resultado;
}

int main() {

  char *palabras[N_PALABRAS] = {"gato",      "perro",    "casa",     "persona",
                                "parque",    "arbol",    "edificio", "calle",
                                "argentina", "santa fe", "rosario",  "unr",
                                "edya",      "farmacia", "tiempo",   "celular"};

  // Creamos un arbol vacio y le insertamos las palabras
  BSTree arbol = bstee_crear(copiar_cadena, comparar_cadena, destruir_cadena);
  for (int i = 0; i < N_PALABRAS; i++)
    bstree_insertar(arbol, palabras[i]);

  // Imprimir el arbol inorden (alfabetico)
  printf("Recorrido inorden: ");
  bstree_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_cadena, NULL);
  puts("");

  int numeros[] = {8, 5, 4, 6, 7, 11, 10, 13, 12, 14};
  int dimension = sizeof numeros / sizeof numeros[0];
  void *valores[dimension];
  for (int i = 0; i < dimension; i++) {
    valores[i] = numeros + i;
  }
  BSTree arbol01 = bts_crear_desde_preorden(
      valores, dimension, (FuncionCopiadora)copiar_int,
      (FuncionComparadora)cmp_int, (FuncionDestructora)eliminar_int);
  gbtree_imprimir(arbol01, (FuncionVisitante)imprimir_entero);
  gbtree_imprimir(arbol, (FuncionVisitante)imprimir_string);

  // Buscar elementos
  assert(bstree_buscar(arbol, "farmacia") == 1);
  assert(bstree_buscar(arbol, "santa fe") == 1);
  assert(bstree_buscar(arbol, "persona") == 1);
  assert(bstree_buscar(arbol, "unr") == 1);
  assert(bstree_buscar(arbol, "argentina") == 1);
  assert(bstree_buscar(arbol, "telefono") == 0);
  assert(bstree_buscar(arbol, "mail") == 0);
  assert(bstree_buscar(arbol, "parques") == 0);
  assert(bstree_buscar(arbol, "EDyA1") == 0);

  // Destruir arbol
  bstree_destruir(arbol);
  bstree_destruir(arbol01);

  return 0;
}