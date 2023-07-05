#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAC_CARGA 0.5

Usuario *crear_usuario(char *DNI, char *tel, int dias) {
  Usuario *nuevo_usuario = malloc(sizeof(Usuario));
  nuevo_usuario->DNI = malloc(sizeof(char) * (strlen(DNI) + 1));
  strcpy(nuevo_usuario->DNI, DNI);
  nuevo_usuario->tel = malloc(sizeof(char) * (strlen(tel) + 1));
  strcpy(nuevo_usuario->tel, tel);
  nuevo_usuario->dias = dias;
  return nuevo_usuario;
}

void eliminar_usuario(Usuario *user) {
  free(user->DNI);
  free(user->tel);
  free(user);
}

Usuario *copiar_usuario(Usuario *u1) {
  return crear_usuario(u1->DNI, u1->tel, u1->dias);
}

void imprimir_usuario(Usuario *u1) {
  printf(
      "Usuario con DNI: %s, telefono: %s y %i días como suscriptor.\n", u1->DNI,
      u1->tel, u1->dias);
}

Espera crear_cola(unsigned capacidad) {
  Espera cola = malloc(sizeof(struct _Espera));
  cola->elementos = calloc((capacidad + 1), sizeof(Usuario *));
  cola->capacidad = capacidad;
  cola->cantElem = 0;
  return cola;
}

void eliminar_cola(Espera cola) {
  for (int i = 1; i <= cola->cantElem; i++)
    eliminar_usuario(cola->elementos[i]);
  free(cola->elementos);
  free(cola);
}

void agregar_cola(Espera cola, Usuario *usuario) {

  if (!cola) return;

  cola->cantElem++;
  if (cola->cantElem == cola->capacidad) {
    cola->capacidad *= 2;
    cola->elementos =
        realloc(cola->elementos, sizeof(Usuario *) * (cola->capacidad + 1));
  }

  cola->elementos[cola->cantElem] = copiar_usuario(usuario);
  Usuario **j = cola->elementos;
  for (unsigned i = cola->cantElem; i > 1 && j[i]->dias > j[i / 2]->dias;
       i /= 2) {
    Usuario *temp = j[i];
    j[i] = j[i / 2];
    j[i / 2] = temp;
  }
}

void eliminar_usuario_cola(Espera cola, Usuario *usuario_a_eliminar) {

  Usuario **usuarios = cola->elementos;
  int condicion = 0;
  int i;
  // Recordar que se suma una vez completado una iteración, luego se fija en la
  // condición.
  for (int k = 1; !condicion && k <= cola->cantElem; k++) {
    // imprimir_usuario(usuarios[k]);
    if (strcmp(usuarios[k]->DNI, usuario_a_eliminar->DNI) == 0) {
      condicion = 1;
      i = k;
    }
  }
  if (!condicion) return;

  // Ahora a eliminarlo
  eliminar_usuario(usuarios[i]);
  usuarios[i] = usuarios[cola->cantElem]; // Muevo el último a la pos.
  usuarios[cola->cantElem] = NULL;
  cola->cantElem--;

  int es_menor = 1;
  while (i * 2 <= cola->cantElem && es_menor) {
    int k = i * 2;
    // Obtengo el mayor de los hijos
    if (k + 1 < cola->cantElem && usuarios[k + 1]->dias > usuarios[k]->dias)
      k = k + 1;
    // Compruebo si se cumple la propiedad
    if (usuarios[i]->dias > usuarios[k]->dias) es_menor = 0;
    // Si no lo hace hay que seguir bajando.
    else {
      Usuario *temp = usuarios[i];
      usuarios[i] = usuarios[k];
      usuarios[k] = temp;
      i = k;
    }
  }
}

void imprimir_1ero_cola(Espera cola) {
  if (cola->elementos[1])
    imprimir_usuario(cola->elementos[1]);
  else
    printf("(null)\n");
}