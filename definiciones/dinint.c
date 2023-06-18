#include "dinint.h"
#include <stdio.h>
#include <stdlib.h>

void int_imprimir(int *data) { printf("%d", *data); }

int *int_copiar(int *entero) {
  int *copia = malloc(sizeof(int));
  *copia = *entero;
  return copia;
}

void int_eliminar(int *entero) { free(entero); };

int int_comparar(int *a, int *b) {
  int resultado = *a - *b;
  return resultado;
}