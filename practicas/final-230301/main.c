#include "metodos.c"
#include <stdio.h>

int main() {

  Usuario *u1 = crear_usuario("44523310", "3416881201", 1);
  Usuario *u2 = crear_usuario("44523311", "3416881201", 2);
  Usuario *u3 =
      crear_usuario("44523312", "3416881201", 0); // No está suscripto.
  Usuario *u4 = crear_usuario("44523313", "3416881201", 30);

  Espera cola = crear_cola(20);
  agregar_cola(cola, u1);
  agregar_cola(cola, u2);
  agregar_cola(cola, u3);
  imprimir_1ero_cola(cola);
  agregar_cola(cola, u4);

  eliminar_usuario_cola(cola, u2);
  imprimir_1ero_cola(cola);
  eliminar_usuario_cola(cola, u4);
  imprimir_1ero_cola(cola);
  eliminar_usuario_cola(cola, u1);
  imprimir_1ero_cola(cola);
  eliminar_usuario_cola(cola, u3);
  imprimir_1ero_cola(cola);

  eliminar_usuario(u1);
  eliminar_usuario(u2);
  eliminar_usuario(u3);
  eliminar_usuario(u4);
  eliminar_cola(cola);
  return 0;
}