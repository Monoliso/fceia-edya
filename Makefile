# Este Makefile tuvo bastantes modificaciones, ver notas.

SHELL = /bin/sh
CFLAGS = -Wall -Wextra -Werror -std=c99

objetivos: $(OBJETIVO)

Practica01: matriz_uni.o

bin/matriz_bi: ./src/Practica01.c ./src/matriz_bi.c

bin/Practica00: src/Practica00.c

02: practicas/02.c estructuras/slist.c estructuras/dlist.c \
		estructuras/cdlist.c estructuras/glist.c practicas/02-contacto.c
	$(CC) $(CFLAGS) $^ -o bin/$@

02-extra: practicas/02-extra.c estructuras/slist.c
	$(CC) $(CFLAGS) $^ -o bin/$@

.PHONY: clean
clean:
	$(RM) bin/*
	$(RM) obj/*