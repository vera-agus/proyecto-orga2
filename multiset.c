#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "multiset.h"

struct trie
{
  int cantidad; // Cantidad de veces que aparece esa palabra en el multiset
  struct trie *siguiente[26];
}

//Metodos de TDA multiset.

/**
 Crea un multiset vacío de palabras y lo devuelve.
**/
multiset_t *multiset crear()
{

}

/**
 Inserta la palabra s al multiset m.
**/
void multiset_insertar(multiset_t *m, char *s)
{

}

/**
 Devuelve la cantidad de repeticiones de la palabra s en el multiset m.
**/
int multiset_cantidad(multiset_t *m, char *s)
{

}

/**
 Devuelve una lista de tipo lista t ordenada según la función f con todos los elementos del multiset m y la cantidad de apariciones de cada uno.
**/
lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t,elemento_t))
{

}

/**
 Elimina el multiset m liberando el espacio de memoria reservado. Luego de la invocación m debe valer NULL.
**/
void multiset_eliminar(multiset_t **m)
{

}
