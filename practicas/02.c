#include "../estructuras/cdlist.h"
#include "../estructuras/dlist.h"
#include "../estructuras/glist.h"
#include "../estructuras/slist.h"
#include "02-contacto.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(int dato) { printf("%d ", dato); }

void ejercicio_02() {

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_destruir(lista);
}

void ejercicio_04() {

  DList lista_doble = dlist_crear();

  lista_doble = dlist_agregar_inicio(lista_doble, 3);
  lista_doble = dlist_agregar_inicio(lista_doble, 2);
  lista_doble = dlist_agregar_inicio(lista_doble, 1);
  lista_doble = dlist_agregar_final(lista_doble, 4);
  lista_doble = dlist_agregar_final(lista_doble, 5);

  dlist_recorrer(lista_doble, imprimir_entero, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");
  dlist_recorrer(lista_doble, imprimir_entero, DLIST_RECORRIDO_HACIA_ATRAS);
  puts("");
  dlist_destruir(lista_doble);
}

void ejercicio_05() {

  CDList lista_circular = cdlist_crear();

  lista_circular = cdlist_agregar_inicio(lista_circular, 10);
  lista_circular = cdlist_agregar_inicio(lista_circular, 9);
  lista_circular = cdlist_agregar_inicio(lista_circular, 8);
  lista_circular = cdlist_agregar_inicio(lista_circular, 7);
  lista_circular = cdlist_agregar_inicio(lista_circular, 6);

  cdlist_recorrer(
      lista_circular, imprimir_entero, DLIST_RECORRIDO_HACIA_ADELANTE
  );
  printf("\n");
  cdlist_recorrer(lista_circular, imprimir_entero, DLIST_RECORRIDO_HACIA_ATRAS);
  printf("\n");

  cdlist_destruir(lista_circular);
}

void ejercicio_07(Contacto **contactos) {
  GList lista = glist_crear();

  for (int i = 0; i < 6; ++i) {
    lista =
        glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
  }

  GList lista_filtrada = glist_filtrar(
      lista, (FuncionCopia)contacto_copia, (Predicado)contacto_mayores_sesenta
  );
  printf("\nLista:\n");
  glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);
  printf("\nLista filtrada:\n");
  glist_recorrer(lista_filtrada, (FuncionVisitante)contacto_imprimir);

  glist_destruir(lista, (FuncionDestructora)contacto_destruir);
  glist_destruir(lista_filtrada, (FuncionDestructora)contacto_destruir);
}

void ejercicio_08(Contacto **contactos) {
  SGList lista_ordenada_nombre = sglist_arr(
      (void **)contactos, 6, (FuncionCopia)contacto_copia,
      (FuncionComparadora)contacto_comparar
  );
  SGList lista_ordenada_edad = sglist_arr(
      (void **)contactos, 6, (FuncionCopia)contacto_copia,
      (FuncionComparadora)contacto_comparar_edad
  );

  Contacto contacto_a_buscar = {"Dardo Fuseneco", "3416894526", 64};
  if (sglist_buscar(
          lista_ordenada_nombre, &contacto_a_buscar,
          (FuncionComparadora)contacto_comparar
      )) {
    printf("\nEl elemento está en la lista\n");
  } else {
    printf("\nEl elemento no está en la lista\n");
  }

  printf("\nLista ordenada por nombre:\n");
  sglist_recorrer(lista_ordenada_nombre, (FuncionVisitante)contacto_imprimir);
  sglist_destruir(lista_ordenada_nombre, (FuncionDestructora)contacto_destruir);
  printf("\nLista ordenada por edad:\n");
  sglist_recorrer(lista_ordenada_edad, (FuncionVisitante)contacto_imprimir);
  sglist_destruir(lista_ordenada_edad, (FuncionDestructora)contacto_destruir);
}

int main() {

  ejercicio_02();
  ejercicio_04();
  ejercicio_05();

  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  ejercicio_07(contactos);
  ejercicio_08(contactos);

  for (int i = 0; i < 6; ++i) {
    contacto_destruir(contactos[i]);
  }

  return 0;
}
