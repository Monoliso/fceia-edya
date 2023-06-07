#include "old_matriz.h"
#include <stdio.h>

// (crear, destruir, escribir una posición, leer de
// una posición)

Matriz *crear(int x, int y) {
  Matriz *matriz;

  matriz          = malloc(sizeof(Matriz));
  matriz->x       = x;
  matriz->y       = y;
  matriz->mat.uni = malloc(x * y * sizeof(float));

  return matriz;
}

void destruir(Matriz *matriz) {
  free(matriz->mat.uni);
  free(matriz);
}

void escribir(Matriz *matriz, int pos_x, int pos_y, float num) {
  if (pos_x > matriz->x || pos_y > matriz->y || pos_x < 0 || pos_y < 0) {
    printf("pelotudoooo\n");
    return;
  }

  matriz->mat.uni[pos_x * matriz->x + pos_y] = num;
}