#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

int contador_operaciones = 0;

int string_len(char *arreglo) {
    if (*arreglo == '\0')
        return 0;
    else
        return 1 + string_len(arreglo + 1);
}

void string_reverse(char *arreglo) {
    int largo = string_len(arreglo);
    for (int i = 0; i <= largo / 2; i++) {
        char caracter            = arreglo[i];
        arreglo[i]               = arreglo[(largo - 1) - i];
        arreglo[(largo - 1) - i] = caracter;
    }
}

int string_concat(char *arreglo, char *otro_arreglo, int max) {
    // Ridiculo este ejercicio
    int i;
    int largo = string_len(arreglo);
    for (i = 0; i < max; i++)
        arreglo[largo + i] = otro_arreglo[i];
    return i;
}

int string_compare(char *arreglo, char *otro_arreglo) {
    int peso_01 = 0, peso_02 = 0;
    for (int i = 0; i < string_len(arreglo); i++)
        peso_01 += arreglo[i];
    for (int i = 0; i < string_len(otro_arreglo); i++)
        peso_02 += otro_arreglo[i];
    int resultado = (peso_01 < peso_02) ? -1 : ((peso_01 == peso_02) ? 0 : 1);
    return resultado;
}

int string_subcadena(char *arreglo, char *otro_arreglo) {
    arreglo[0] = otro_arreglo[0];
    return 1;
}

void ejercicio_02(char *arreglo) {
    string_reverse(arreglo);
    char otro_arreglo[]     = "hijk";
    int caracteres_copiados = string_concat(arreglo, otro_arreglo, 1);
    int peso                = string_compare(arreglo, otro_arreglo);
    int indice_subcadena    = string_subcadena(arreglo, otro_arreglo);
    printf(
        "El arreglo es \"%s\" y la cantidad de caracteres copiados es %i\n",
        arreglo, caracteres_copiados
    );
    printf("El peso entre los arreglos es %i\n", peso);
    printf(
        "La primera ocurrencia del arreglo \"otro_arreglo\" dentro de "
        "arreglo es: %i\n",
        indice_subcadena
    );
}

void ejercicio_05() {
    Matriz *matriz_01 = crear_matriz(4, 4);
    escribir_matriz(matriz_01, 3, 2, 6.125);
    // matriz_insertar_fila(matriz_01, 5);
    matriz_intercambiar_filas(matriz_01, 3, 4);
    leer_matriz(matriz_01, 4, 2);
    destruir_matriz(matriz_01);
}

int main() {
    // char mi_arreglo[] = "abcdefg";
    // ejercicio_02(mi_arreglo);
    ejercicio_05();
    return 0;
}