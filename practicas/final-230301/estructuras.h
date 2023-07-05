typedef unsigned (*FHash)(void *);

typedef struct {
  char *DNI;
  char *tel;
  int dias; // Representa el tiempo (en dias) desde que son premiums. Si es nulo
            // significa que no están suscriptos.
} Usuario;

struct _Casilla {
  Usuario *usuario;
};

typedef struct _Espera {
  Usuario **elementos;
  unsigned cantElem;
  unsigned capacidad;
} *Espera;

typedef struct _Usuarios {
  struct _Casilla **elementos;
  int cantElem;
  unsigned capacidad;
  FHash hash;
} *Usuarios;