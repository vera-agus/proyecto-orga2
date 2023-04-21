//#include <stdio.h>
//#include <stdlib.h>
//#include "define.h"

#ifndef MULTISET_H_INCLUDED
#define MULTISET_H_INCLUDED

#include "listaordenada.h"

//Structs para la manipulación del multiset.

struct trie;
typedef struct trie multiset_t;

// ---------------------------------------------------------------------------------------------
// Definición de prototipos y documentación de las funciones.
// ---------------------------------------------------------------------------------------------

//Metodos de TDA multiset.

/**
 Crea un multiset vacío de palabras y lo devuelve.
**/
extern multiset_t *multiset crear();

/**
 Inserta la palabra s al multiset m.
**/
extern void multiset_insertar(multiset_t *m, char *s);

/**
 Devuelve la cantidad de repeticiones de la palabra s en el multiset m.
**/
extern int multiset_cantidad(multiset_t *m, char *s);

/**
 Devuelve una lista de tipo lista t ordenada según la función f con todos los elementos del multiset m y la cantidad de apariciones de cada uno.
**/
extern lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t,elemento_t)); 

/**
 Elimina el multiset m liberando el espacio de memoria reservado. Luego de la invocación m debe valer NULL.
**/
extern void multiset_eliminar(multiset_t **m);

#endif // MULTISET_H_INCLUDED
