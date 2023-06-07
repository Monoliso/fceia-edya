typedef union {
    float* uni;
    float** bidi;
} MatUnion;

typedef struct {
    MatUnion mat;
    int x;
    int y;
} Matriz;

/*(crear, destruir, escribir una posición, leer de
una posición)*/

Matriz* crear_matriz(int x, int y);

void destruir_matriz(Matriz* matriz);

void escribir_matriz(Matriz* matriz, int pos_x, int pos_y, float num);

float leer_matriz(Matriz* matriz, int pos_x, int pos_y);