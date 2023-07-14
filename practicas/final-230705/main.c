#include "../05-contacto.h"
#include "tablahash.h"
#include <stdio.h>

int main() {
  TablaHash tabla = tablahash_crear(
      16, (FuncionCopiadora)contacto_copia,
      (FuncionComparadora)contacto_comparar,
      (FuncionDestructora)contacto_destruir,
      (FuncionImpresora)contacto_imprimir, (FuncionHash)contacto_heashear);

  int cant_contactos = 7;
  Contacto *agenda[cant_contactos];
  agenda[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  agenda[1] = contacto_crear("Moni Argento", "3412684759", 60);
  agenda[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  agenda[3] = contacto_crear("Paola Argento", "3416259862", 29);
  agenda[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  agenda[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);
  agenda[6] = contacto_crear("Luca Seri", "3416881201", 20);

  for (int i = 0; i < cant_contactos; i++) {
    tablahash_insertar(tabla, agenda[i]);
  }
  puts("\nTablita:");
  tablahash_imprimir(tabla);

  printf("\nEl cluster de mayor tamaño es %d\n", tablahash_max_cluster(tabla));

  printf("Buscando...\n");
  Contacto *c1 = tablahash_buscar(tabla, agenda[0]);
  if (c1) {
    printf("El contacto ");
    contacto_imprimir(c1);
    printf(" fue encontrado.\n");
  }

  printf("Eliminando contacto...\n");
  tablahash_eliminar(tabla, agenda[0]);
  Contacto *c11 = tablahash_buscar(tabla, agenda[0]);
  if (!c11) {
    printf("El contacto ");
    contacto_imprimir(agenda[0]);
    printf(" no se encontró.\n");
  }

  for (int i = 0; i < cant_contactos; i++) {
    contacto_destruir(agenda[i]);
  }
  contacto_destruir(c1);
  tablahash_destruir(tabla);

  return 0;
}