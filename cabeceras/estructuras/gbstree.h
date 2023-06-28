#ifndef __BSTREE_ALT_H__
#define __BSTREE_ALT_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionImpresora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

// Inicialmente creí que era de interes tener la definición superior en la
// cabecera para ver sus partes. Creo que en realidad era mantener *también*
// esta definición en la implementación para no poder acceder a sus miembros
// directamente, sino a través de métodos. Sin embargo si quisieramos hacerlo,
// es necesario cambiar en la definición del puntero a la raiz con como está
// abajo. Eso es porque con la palabra struct puedo hacer el puntero opaco, por
// lo que se puede compilar.
//
// struct _BSTree {
//   struct _BST_Nodo *raiz;
//   FuncionCopiadora copia;
//   FuncionComparadora comp;
//   FuncionDestructora destr;
// };

/*
  Tenemos los árboles generales. Tenemos los árboles generales con esteroides,
  que tienen las funciones para copiar, comparar y destruir los elementos.
  Cualquier árbol binario de búsqueda puede ser uno general. Con los métodos
  adecuados funciona. También podemos hacer que los BST sean de enteros, pero
  limitan. Para la función de impresión se puede hacer una interfaz que utilice
  el método generalizado para el caso en especifico. Por lo tanto tendríamos un
  btree_imprimir() que llama a la versión generalizada con las funciones
  adecuadas.
*/

typedef struct _BSTree *BSTree;

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

/**
 * Retorna un arbol de busqueda binaria vacio.
 * Por unica vez se piden por parametro los punteros a funcion.
 */
BSTree bstee_crear(
    FuncionCopiadora, FuncionComparadora, FuncionDestructora, FuncionImpresora);

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
void bstree_insertar(BSTree, void *);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(
    BSTree, BSTreeRecorrido, FuncionVisitanteExtra, void *extra);

/**
 * Genera un árbol con los datos en preorden.
 */
BSTree bts_crear_desde_preorden(
    void **preorden, int dimension, FuncionCopiadora, FuncionComparadora,
    FuncionDestructora, FuncionImpresora);

/**
 * Imprime una gráfica del árbol.
 */
void bstree_imprimir(BSTree arbol);

#endif //__BSTREE_ALT_H__