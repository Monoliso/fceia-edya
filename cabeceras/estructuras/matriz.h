typedef struct {
    union {
        float* uni;
        float** bidi;
    };
    int x;
    int y;
} Matriz;

/*(crear, destruir, escribir una posición, leer de
una posición)*/

Matriz* crear_matriz(int x, int y);

void destruir_matriz(Matriz* matriz);

int existe_posicion_matriz(Matriz* matriz, int pos_x, int pos_y);

void escribir_matriz(Matriz* matriz, int pos_x, int pos_y, float num);

void leer_matriz(Matriz* matriz, int pos_x, int pos_y);

void matriz_intercambiar_filas(Matriz* matriz, int fila_01, int fila_02);

void matriz_insertar_fila(Matriz* matriz, int posicion);