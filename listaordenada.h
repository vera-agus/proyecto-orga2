//#include <stdio.h>
//#include <stdlib.h>

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "define.h"

typedef enum 
{
  ELEM1_MAYOR_QUE_ELEM2,
  ELEM1_IGUAL_QUE_ELEM2,
  ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;

struct elemento 
{
  int a;
  char *b;
};

//Structs para la manipulación de la lista
typedef struct elemento elemento_t;

typedef comparacion_resultado_t (funcion_comparacion_t) (
  elemento_t *elem1, elemento_t *elem2
);

typedef struct lista lista_t;

// ---------------------------------------------------------------------------------------------
// Definición de prototipos y documentación de las funciones.
// ---------------------------------------------------------------------------------------------

//Metodos TDA lista.

/**
 Crea una lista vacía y la devuelve.
**/
extern lista_t *lista crear();

/**
 Inserta el elemento elem en la posición pos de la lista.
**/
extern int lista_insertar(lista t *l, elemento_t elem, unsigned int pos);

/**
Elimina el elemento de la posición pos de la lista.
**/
extern elemento_t *lista_eliminar(lista_t *l, unsigned int pos); 

/**
 Devuelve un puntero al elemento que ocupa la posición pos de la lista.
**/
extern elemento_t *lista_elemento(lista_t *l, unsigned int pos); 

/**
Dada la lista l y la función comparar ordena la lista de acuerdo al criterio de dicha función.
**/
extern int lista_ordenar(lista_t *l, funcion comparacion_t comparar);

/**
Devuelve la cantidad de elementos de la lista l.
**/
extern unsigned int lista_cantidad(lista_t *l); 

/**
Devuelve verdadero (̸= 0) si la lista está vacía, y falso (= 0) si la lista contiene al menos un elemento.
**/
extern int lista_vacia(list_t lista);

#endif // LISTA_H_INCLUDED
