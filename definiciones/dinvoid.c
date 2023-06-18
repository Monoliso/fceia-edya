#include "dinvoid.h"
#include <stdlib.h>

void *id(void *dato) { return dato; }
void vacio(void *dato) { id(dato); }