#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// (crear, destruir, escribir una posición, leer de
// una posición)

Matriz* crear_matriz(int x, int y){
    Matriz* matriz = malloc(sizeof(Matriz));
    matriz->x = x;
    matriz->y = y;
    matriz->uni = malloc(sizeof(float)*(x*y));
    return matriz;
}

void destruir_matriz(Matriz* matriz){
    free(matriz->uni);
    free(matriz);
}

int existe_posicion_matriz(Matriz* matriz, int pos_x, int pos_y){
    return (pos_x < matriz->x || pos_y < matriz->y || pos_x > 0 || pos_y > 0) ? 1 : 0;
}

void escribir_matriz(Matriz* matriz, int pos_x, int pos_y, float num){
    if (existe_posicion_matriz(matriz, pos_x, pos_y)){
        matriz->uni[pos_x*matriz->x + pos_y] = num;
    } else {
        printf("pelotudoooo\n");
    }
}

void leer_matriz(Matriz* matriz, int pos_x, int pos_y){
    if(existe_posicion_matriz(matriz, pos_x, pos_y)) 
        printf("El valor en la posición (%i, %i) es %f\n", pos_x, pos_y, 
            matriz->uni[pos_x*matriz->x + pos_y]);
}

void matriz_intercambiar_filas(Matriz* matriz, int fila_01, int fila_02){
    int filas = matriz->x;
    if(existe_posicion_matriz(matriz, fila_01, 0) && existe_posicion_matriz(matriz, fila_02, 0)){
        for(int columna=0; columna < matriz->y; columna++){
            float temporal = matriz->uni[fila_01*filas + columna];
            matriz->uni[fila_01*filas + columna] = matriz->uni[fila_02*filas + columna];
            matriz->uni[fila_02*filas + columna] = temporal;
        }
    }
}

// Preguntar cuál es preferible
// void matriz_intercambiar_filas(Matriz* matriz, int fila_01, int fila_02){
//     if(!existe_posicion_matriz(matriz, fila_01, 0) || existe_posicion_matriz(matriz, fila_02, 0)){
//         return;
//     }
//     for(){

//     }
// }

// void insertar_fila_matriz(Matriz* matriz, int posicion){
//     if(existe_posicion_matriz(matriz, posicion-1, 0)){

//     }
// }