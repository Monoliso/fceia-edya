#include "dinstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_imprimir(char *data) { printf("%s", data); }

int str_comparar(char *dato1, char *dato2) { return strcmp(dato1, dato2); }

char *str_copiar(char *dato) {
  char *str = malloc(sizeof(char) * (strlen(dato) + 1));
  strcpy(str, dato);
  return str;
}

void str_destruir(char *cadena) { free(cadena); }