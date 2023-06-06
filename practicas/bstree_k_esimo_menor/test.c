#include "bstree.h" /* funciones de ABB */
#include <assert.h> /* funcion assert*/
#include <stdlib.h> /* definicion de NULL */
#include <stdio.h> /* definicion de printf*/

static void *f_copiar(void *dato) {
  int *copia = malloc(sizeof(int));
  *copia = *((int *) dato);
  return copia; 
}

static int f_comp(void *dato1, void *dato2) {
  return *((int *)dato1) - *((int *)dato2);
}

static void f_destruir (void *dato) {
  free(dato);
}

static void f_recorrer(void *dato, __attribute__((unused)) void *extra) {
  printf("%d ", *((int *)dato));
}

int main (void) {
  BSTree arbol = bstree_crear();
  /* Caso base para el árbol vacío. */
  assert(bstree_k_esimo_menor(arbol, 0) == NULL);
  int j;
  /* Creo un arbol de la forma
              0
            /   \
          -2     1
         /   \    \
       -3    -1    2
                    \
                     3
                    / \
               números random */
  j = 0;
  arbol = bstree_insertar(arbol, &j, f_copiar, f_comp);
  j = -2;
  arbol = bstree_insertar(arbol, &j, f_copiar, f_comp);
  j = -1;
  arbol = bstree_insertar(arbol, &j, f_copiar, f_comp);
  j = -3;
  arbol = bstree_insertar(arbol, &j, f_copiar, f_comp);
  for (int i = 1; i < 4; i++) 
    arbol = bstree_insertar(arbol, &i, f_copiar, f_comp);
  for (int i = 0; i < 15; ++i) {
    int i = rand() % 100;
    arbol = bstree_insertar(arbol, &i, f_copiar, f_comp);
  }
  /* Veo en pantalla el orden de los elementos. */
  puts("Recorrido IN");
  bstree_recorrer(arbol, BTREE_RECORRIDO_IN, f_recorrer, NULL);
  puts("");
  /* Test de bstree_k_esimo_menor en diferentes casos. */
  assert( *((int *)bstree_k_esimo_menor(arbol, 0)) == -3);  
  assert( *((int *)bstree_k_esimo_menor(arbol, 1)) == -2);  
  assert( *((int *)bstree_k_esimo_menor(arbol, 2)) == -1);  
  assert( *((int *)bstree_k_esimo_menor(arbol, 5)) == 2);
  assert( bstree_k_esimo_menor(arbol, 30) == NULL);  
  assert( bstree_k_esimo_menor(arbol, -1) == NULL);  
  bstree_destruir(arbol, f_destruir);
  return 0;
}
