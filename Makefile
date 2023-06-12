# Este Makefile tuvo bastantes modificaciones, ver notas.

SHELL = /bin/sh
CFLAGS = -g -Wall -Wextra -Werror -std=c99
CABECERAS= ./cabeceras
# Variable de interes: VPATH
# TODO: Reemplazar las reglas implicitas para borrar varias de las líneas repetidas.

objetivos: $(OBJETIVO)

02: practicas/02.c definiciones/slist.c definiciones/dlist.c \
		definiciones/cdlist.c definiciones/glist.c practicas/02-contacto.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

02-extra: practicas/02-extra.c/slist.c
	$(CC) $(CFLAGS) $^ -o bin/$@

03: practicas/03.c definiciones/gqueue.c definiciones/gstack.c definiciones/glist.c practicas/02-contacto.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

btree: practicas/test.c definiciones/btree.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

04-02: practicas/04-02.c obj/gheaps.o
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

obj/gheaps.o: definiciones/gheaps.c cabeceras/estructuras/gheaps.h
	$(CC) $(CFLAGS) -I$(CABECERAS) $< -c -o $@

.PHONY: clean
clean:
	$(RM) bin/*
	$(RM) obj/*