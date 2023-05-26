#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFERSIZE 100
#define TAMANIO_AGENDA 100


char* ejercicio_06() {
    // get_new_line
    char buffer[BUFFERSIZE];
    scanf("%s", buffer);
    char *ingreso = malloc(sizeof(buffer));
    strcpy(ingreso, buffer);
    return ingreso;
}


// 13
typedef enum {ORO, COPA, BASTO, ESPADA} Palos;

typedef struct {
    int valor;
    Palos palo;
} Carta;

typedef struct {
    Carta cartas[48];
} Mazo;

void llenar_13(Mazo *mi_mazo) {
    int indice_carta = 0;
    for(int i=0; i < 4; i++) {
        for(int x=0; x < 12; x++) {
            indice_carta = i*12 + x;
            mi_mazo->cartas[indice_carta].palo = i;
            mi_mazo->cartas[indice_carta].valor = x + 1;
       } 
    }
}

Carta azar_13(Mazo *mi_mazo) {
    srand(time(NULL));
    int aleatorio = rand() % 48;
    Carta carta_aleatoria = mi_mazo->cartas[aleatorio];
    return carta_aleatoria;
}

void ejercicio_13() {
    Mazo *mi_mazo = malloc(sizeof(Mazo));
    llenar_13(mi_mazo);
    azar_13(mi_mazo);
    free(mi_mazo);
}


// 14
typedef struct {
    char* nombre;
    char* numero_celular;
    unsigned int edad;
} Contacto;

typedef struct {
    int cantidad;
    Contacto contactos[TAMANIO_AGENDA];
} Agenda;

Contacto crear_contacto() {
    Contacto nuevo_contacto;
    printf("Ingrese el nombre: ");
    nuevo_contacto.nombre = ejercicio_06();
    printf("Ingrese el numero celular: ");
    nuevo_contacto.numero_celular = ejercicio_06();
    printf("Ingrese la edad: ");
    scanf("%u", &nuevo_contacto.edad);
    return nuevo_contacto;
}

void actualizar_edad(Contacto* contacto) {
    printf("Ingrese una nueva edad: ");
    scanf("%u", &contacto->edad);

    // Para "actualizar" la edad es necesario que sea un puntero, pues sino lo que 
    // tendremos es una copia con la edad modificada, y la función está definida para no
    // devolver nada
}

void alta_contacto(Agenda* mi_agenda) {
    int indice = mi_agenda->cantidad;
    mi_agenda->contactos[indice] = crear_contacto();
    mi_agenda->cantidad++;
}

void modificar_edad(Agenda* mi_agenda) {
    Contacto* contacto;
    char* contacto_deseado;
    printf("Ingrese el contacto al que le quiere cambiar la edad: ");
    contacto_deseado = ejercicio_06();
    for (int i=0; i < mi_agenda->cantidad; i++) {
        contacto = &mi_agenda->contactos[i];
        if (!strcmp(contacto->nombre, contacto_deseado))
            actualizar_edad(contacto);
    }
    free(contacto_deseado);
}

void imprimir_contactos(Agenda* mi_agenda) {
    Contacto* contacto;
    printf("Los contactos de su agenda son:\n");
    for (int i=0; i < mi_agenda->cantidad; i++) {
        contacto = &mi_agenda->contactos[i];
        printf("{nombre: %s, numero_celular: %s, edad: %i}\n", contacto->nombre,
               contacto->numero_celular, contacto->edad);
    }
}

double prom(Agenda* mi_agenda) {
    int suma_edades = 0;
    for (int i=0; i < mi_agenda->cantidad; i++) {
        suma_edades += mi_agenda->contactos[i].edad;
    }
    double promedio = (float)suma_edades/mi_agenda->cantidad;
    return promedio;
}

void freeContacto(Contacto mi_contacto) {
    free(mi_contacto.nombre);
    free(mi_contacto.numero_celular);
}

void freeAgenda(Agenda* mi_super_agenda) {
    for(int i=0; i < TAMANIO_AGENDA; i++) {
        freeContacto(mi_super_agenda->contactos[i]);
    }
    free(mi_super_agenda);
}

Agenda* inicializar_agenda() {
    Agenda* mi_agenda = malloc(sizeof(Agenda));
    *mi_agenda = (Agenda) {.cantidad = 0 };
    return mi_agenda;
}

void ejercicio_14() {
    Contacto nuevo_contacto = crear_contacto();
    actualizar_edad(&nuevo_contacto);
    Agenda* nueva_agenda = inicializar_agenda();
    alta_contacto(nueva_agenda);
    modificar_edad(nueva_agenda);
    alta_contacto(nueva_agenda);
    imprimir_contactos(nueva_agenda);
    printf("%lf\n", prom(nueva_agenda));
    freeContacto(nuevo_contacto);
    freeAgenda(nueva_agenda);
}


// 
int main() {
    printf("\033[H\033[J");

    char* i = ejercicio_06();
    free(i);
    ejercicio_13();
    ejercicio_14();

    return 0;
}