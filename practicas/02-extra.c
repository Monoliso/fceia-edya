#include "../estructuras/slist.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(int dato) { printf("%c ", dato); }

SList slist_sufijo(SList lista01, SList lista02) {

  if (slist_vacia(lista01) || slist_vacia(lista02)) return NULL;
  SList lista01_invertida = slist_invertir(lista01);
  SList lista02_invertida = slist_invertir(lista02);
  SList lista_sufijo      = slist_crear();

  SList nodo01 = lista01_invertida;
  SList nodo02 = lista02_invertida;

  while (nodo01 != NULL && nodo02 != NULL && nodo01->dato == nodo02->dato) {
    lista_sufijo = slist_agregar_inicio(lista_sufijo, nodo01->dato);
    nodo01       = nodo01->sig;
    nodo02       = nodo02->sig;
  }

  slist_destruir(lista01_invertida);
  slist_destruir(lista02_invertida);
  return lista_sufijo;
}

int slist_palindromo(SList lista) {

  if (slist_vacia(lista)) return 0;
  SList lista_invertida = slist_invertir(lista);
  SList nodo01          = lista_invertida;

  while (nodo01 != NULL && lista->dato == nodo01->dato) {
    nodo01 = nodo01->sig;
    lista  = lista->sig;
  }

  int resultado = (nodo01 == NULL);
  slist_destruir(lista_invertida);
  return resultado;
}

SList voltear(SList lista) {
  SList previa = lista;

  if (lista == NULL || lista->sig == NULL) {
    return lista;
  }

  lista = voltear(lista->sig);

  previa->sig->sig = previa;
  previa->sig      = NULL;

  return lista;
}

void slist_intercalar(SList lista) {
  SList aux;
  if (lista == NULL) return;

  SNodo *liebre = lista, *tortuga = lista;
  while (liebre != NULL) {
    liebre = liebre->sig;
    if (liebre) {
      liebre  = liebre->sig;
      tortuga = tortuga->sig;
    }
  }

  SList segundaMitad = tortuga->sig;
  tortuga->sig       = NULL;
  segundaMitad       = voltear(segundaMitad);

  while (segundaMitad != NULL) {
    aux               = segundaMitad->sig;
    segundaMitad->sig = lista->sig;
    lista->sig        = segundaMitad;
    lista             = segundaMitad->sig;
    segundaMitad      = aux;
  }
}

int main() {

  int elementos01[]  = {119, 97, 108, 107, 105, 110, 103};
  int elementos02[]  = {108, 105, 115, 116, 101, 110, 105, 110, 103};
  int elementos03[]  = {107, 97, 121, 97, 107};
  int elementos04[]  = {97, 108, 115, 100, 99, 105, 112};
  SList lista01      = slist_arr(elementos01, 7);
  SList lista02      = slist_arr(elementos02, 9);
  SList lista03      = slist_arr(elementos03, 5);
  SList lista04      = slist_arr(elementos04, 7);
  SList lista_sufijo = slist_sufijo(lista01, lista02);
  slist_intercalar(lista04);

  slist_recorrer(lista01, imprimir_entero);
  puts("");
  slist_recorrer(lista02, imprimir_entero);
  puts("");
  slist_recorrer(lista_sufijo, imprimir_entero);
  puts("");
  if (slist_palindromo(lista03))
    printf("Es palindromo\n");
  else
    printf("No es palindromo\ns");

  lista01 = voltear(lista01);
  slist_recorrer(lista01, imprimir_entero);
  puts("");

  slist_intercalar(lista01);
  slist_recorrer(lista01, imprimir_entero);
  puts("");

  // ejercicio5();

  slist_destruir(lista01);
  slist_destruir(lista02);
  slist_destruir(lista03);
  slist_destruir(lista_sufijo);

  return 0;
}
