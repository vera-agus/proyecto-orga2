#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "listaordenada.h"

typedef struct celda
{
  elemento_t elem;
  struct celda *siguiente;
} celda_t;

//typedef struct celda celda_t;

struct lista
{
  celda_t *primera; //puntero a la primera celda de la lista
  int cantidad; // cantidad de elementos de la lista
};

// --------------------------------------------------------------

/**
 Inicializa una lista vacía.
**/
lista_t *lista_crear()
{
  lista_t *lista=(*lista_t)malloc(sizeof(struct lista);
  lista->primera= NULL;
  lista->cantidad= 0;
  return lista;
}

/**
 Inserta el elemento elem en la posición pos de la lista.
**/
int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos)
{ // asumimos que la primera posicion de la lista es 0.
  if(l->cantidad >= pos) //Puede ser igual, en ese caso lo inserta ultimo
  {
    int i;
    celda_t *celda= l->primera;
    for(i= 0; i < pos; i++)
    {
      celda= celda->siguiente;
    }
    celda_t *celdaAux= (*celda_t)malloc(sizeof(celda_t));
    celdaAux->siguiente= celda->siguiente;
    celda->siguiente= celdaAux;
    celdaAux->elem= elem;

    return 0;
  }
  else
    exit(LST_POS_INVALIDA);
}

/**
Elimina el elemento de la posición pos de la lista.
**/
elemento_t *lista_eliminar(lista_t *l, unsigned int pos)
{
    //considerando que cada celda no tiene necesariamente un elemento.
  elemento_t elem;
  elemento_t elem_to_return;
  celda_t *celda= l->primera;
  if(l->cantidad >= pos){
    int i;
    for(i= 0; i < pos; i++){
        celda= celda->siguiente;
    }
    elem= celda->elem;
    elem_to_return= elem;
    elem= NULL;
    free(elem); //es necesario?
    return elem_to_return;
  }
   else
    exit(LST_POS_INVALIDA);
}

/**
 Devuelve un puntero al elemento que ocupa la posición pos de la lista.
**/
elemento_t *lista_elemento(lista_t *l, unsigned int pos)
{
  elemento_t elem_to_return;
  celda_t *celda= l->primera;
  if(l->cantidad >= pos){
    int i;
    for(i= 0; i < pos; i++){
        celda= celda->siguiente;
    }
  elem_to_return= celda->elem;
  return *elem_to_return;
  }
   else
    exit(LST_POS_INVALIDA);
}

/**
Dada la lista l y la función comparar ordena la lista de acuerdo al criterio de dicha función.
**/
int lista_ordenar(lista_t *l, funcion_comparacion_t comparar)
{

}

/**
Devuelve la cantidad de elementos de la lista l.
**/
unsigned int lista_cantidad(lista_t *l)
{
    return l->cantidad; //considerando que cada celda tiene un elem.
}
unsigned int lista_cantidad(lista_t *l)
{
    //considerando que cada celda no necesariamente tiene un elem.
    int contador;
    celda_t *celda= l->primera;
    if(l->cantidad >= pos){
        int i;
        for(i= 0; i < pos; i++){
            celda= celda->siguiente;
    }
}

/**
Devuelve verdadero (̸= 0) si la lista está vacía, y falso (= 0) si la lista contiene al menos un elemento.
**/
int lista_vacia(list_t lista)
{

}*/
