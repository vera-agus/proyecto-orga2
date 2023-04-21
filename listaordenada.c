#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "listaordenada.h"

typedef struct celda 
{
  elemento_t elem;
  struct celda *siguiente;
} celda_t;

typedef struct celda celda_t;

struct lista 
{
  celda_t *primera; //puntero a la primera celda de la lista
  int cantidad; // cantidad de elementos de la lista
};

// --------------------------------------------------------------

/**
 Inicializa una lista vacía.
**/
lista_t *lista crear()
{
  
}

/**
 Inserta el elemento elem en la posición pos de la lista.
**/
int lista_insertar(lista t *l, elemento_t elem, unsigned int pos) //¿Qué queremos que retorne? ¿A que refiere ese int?
{

}

/**
Elimina el elemento de la posición pos de la lista.
**/
elemento_t *lista_eliminar(lista_t *l, unsigned int pos)
{

}

/**
 Devuelve un puntero al elemento que ocupa la posición pos de la lista.
**/
elemento_t *lista_elemento(lista_t *l, unsigned int pos)
{

}

/**
Dada la lista l y la función comparar ordena la lista de acuerdo al criterio de dicha función.
**/
int lista_ordenar(lista_t *l, funcion comparacion_t comparar)
{

}

/**
Devuelve la cantidad de elementos de la lista l.
**/
unsigned int lista_cantidad(lista_t *l)
{

}

/**
Devuelve verdadero (̸= 0) si la lista está vacía, y falso (= 0) si la lista contiene al menos un elemento.
**/
int lista_vacia(list_t lista)
{
  
}
