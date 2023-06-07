# Este Makefile tuvo bastantes modificaciones, ver notas.

SHELL = /bin/sh
CFLAGS = -g -Wall -Wextra -Werror -std=c99
CABECERAS= ./cabeceras

objetivos: $(OBJETIVO)

02: practicas/02.c definiciones/slist.c definiciones/dlist.c \
		definiciones/cdlist.c definiciones/glist.c practicas/02-contacto.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

02-extra: practicas/02-extra.c/slist.c
	$(CC) $(CFLAGS) $^ -o bin/$@

btree: practicas/test.c definiciones/btree.c
	$(CC) $(CFLAGS) -I$(CABECERAS) $^ -o bin/$@

.PHONY: clean
clean:
	$(RM) bin/*
	$(RM) obj/*