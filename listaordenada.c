#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "listaordenada.h"

typedef struct celda {
elemento_t elem;
struct celda *siguiente;
} celda_t;
typedef struct celda celda_t;
struct lista {
3
celda_t *primera; //puntero a la primera celda de la lista
int cantidad; // cantidad de elementos de la lista
};
