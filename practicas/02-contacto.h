#ifndef __CONTACTO_H__
#define __CONTACTO_H__

/**
 * Estructura que representa un contacto.
 */
typedef struct {
  char *nombre;
  char *tel;
  unsigned int edad;
} Contacto;

/**
 * Crea un nuevo contacto.
 */
Contacto *contacto_crear();

/**
 * Crea una copia física del contacto.
 */
Contacto *contacto_copia(Contacto *contacto);

/**
 * Compara el nombre de dos contactos en orden lexicográfico. Devuelve 0 si son
 * iguales, < 0 si el primero es menor que el segundo y > 0 si el primero es
 * mayor que el segundo.
 */
int contacto_comparar(Contacto *c1, Contacto *c2);

/**
 * Función destructora de un contacto.
 */
void contacto_destruir(Contacto *contacto);

/**
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir(Contacto *contacto);

/**
 * Determina si un contacto es mayor de 60 años.
 */
int contacto_mayores_sesenta(Contacto *contacto);

int contacto_comparar_edad(Contacto *c1, Contacto *c2);

#endif /* __CONTACTO_H__ */