#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */

typedef struct _TablaHash *TablaHash;

/**
 * La dinámica con estas cabeceras es poder importarla en un programa que haga
 * uso de los métodos y tipos de datos definidos.
 * Ahora bien, una cosa de interés es que al ser la parte pública de un programa
 * uno puede usar ocultamiento para no tener acceso a los miembros que realmente
 * representan la data que se está almacenando.
 *
 * Una problemática que tengo con los tipos de datos generalizadores es que si
 * se utilizan con otras implementaciones van a haber colisiones, por lo que
 * creo que la mejor idea sería definirla en una cabecera común que importen
 * todos los headers de las estructuras.
 *
 * Respecto a las tablas hash, cómo podemos hacer para construir sus distintas
 * variantes? Respuesta: compilar con distintas implementaciones. Al estar
 * definidas en sus fuentes la cabecera no tiene que ocuparse de saber sus
 * formas de manejar colisiones. De todas formas no hay que olvidar quién es la
 * audiencia. Las cabeceras estas serían para los programadores, no para los
 * usuarios.
 *
 * Y respecto a lo que define a cada tabla hash, su función hash, podemos
 * admitir que toda implementación de una función hash depende del codominio,
 * del tamaño de la tabla, por lo que sería necesario que sea definida en la
 * implementación y en particular en run-time, porque la tabla
 * va variando dinámicamente (el concepto, al menos, es ese; el
 * problema es que no se puede llevar a cabo exactamente en C).
 * Entonces lo único que podemos hacer es pasarle una forma de codificar la
 * información a hashear. Luego se usará eso con el módulo de la dimensión de la
 * tabla.
 */

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash ghashtable_crear(
    unsigned capacidad, FuncionCopiadora copia, FuncionComparadora comp,
    FuncionDestructora destr, FuncionHash hash);

/**
 * Retorna el numero de elementos de la tabla.
 */
unsigned int ghashtable_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
unsigned int ghashtable_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void ghashtable_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void ghashtable_insertar(TablaHash tabla, void *dato);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *ghashtable_buscar(TablaHash tabla, void *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void ghashtable_eliminar(TablaHash tabla, void *dato);

/**
 * Duplica la capacidad de la tabla y reposiciona los elementos.
 */
void ghashtable_redimensionar(TablaHash);

#endif /* __TABLAHASH_H__ */