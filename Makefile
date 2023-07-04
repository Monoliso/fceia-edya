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

04: practicas/04.c definiciones/btree.c definiciones/gqueue.c definiciones/glist.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

04-01: practicas/04-01.c definiciones/gbstree.c definiciones/dinint.c definiciones/dinstr.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

04-02: practicas/04-02.c obj/gheaps.o
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

obj/gheaps.o: definiciones/gheaps.c cabeceras/estructuras/gheaps.h
	$(CC) $(CFLAGS) -I$(CABECERAS) $< -c -o $@

05: practicas/05.c practicas/05-contacto.c practicas/05-utils.c definiciones/ghashtable_lp.c 
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

.PHONY: clean
clean:
	$(RM) bin/*
	$(RM) obj/*