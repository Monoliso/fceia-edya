#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  unsigned int N = *argv[1] - '0', Q = *argv[2] - '0';
  // unsigned int *permutaciones[Q];
  char *palabras[N];
  char buffer[1000001];

  for (int i = 0; i < N; i++) {
    scanf("%s", buffer);
    palabras[i] = malloc(sizeof(char) * strlen(buffer));
    strcpy(palabras[i], buffer);
  }

  for (int i = 0; i < Q; i++) {
  }

  printf("%i %i\n", N, Q);
  return 0;
}
