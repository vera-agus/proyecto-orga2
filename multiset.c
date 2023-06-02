#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "define.h"
#include "multiset.h"
#include "listaordenada.h"

// BEGIN - PROTOTIPOS DE FUNCIONES AUXILIARES
void preorden(multiset_t *m, char *palabra, lista_t* l);
void destruir_elemento(void* elemento);
void destruir(multiset_t *m, void (*destruir_elemento)(void*));
// END - PROTOTIPOS DE FUNCIONES AUXILIARES

struct trie
{
  int cantidad; // Cantidad de veces que aparece esa palabra en el multiset
  struct trie *siguiente[26];
};
//Metodos de TDA multiset.

/**
 Crea un multiset vacío de palabras y lo devuelve.
**/
multiset_t *multiset_crear()
{
    multiset_t *multiset = (multiset_t*) malloc(sizeof(struct trie));
    multiset->cantidad = 0;

    int i;
    for(i = 0; i < 26; i++)
        multiset->siguiente[i] = NULL;

    return multiset;
}

/**
 Inserta la palabra s al multiset m.
**/
void multiset_insertar(multiset_t *m, char *s)
{
    int l = strlen(s);
    int pos;
    multiset_t* multisetActual = m;

    int i;
    for(i = 0; i < l; i++)
    {
        pos = tolower(s[i]) - 'a'; //Unificamos codificación para efectivizar el mapeo de caracteres a números
        if(multisetActual->siguiente[pos] == NULL)
            multisetActual->siguiente[pos] = multiset_crear(); //Porque va descubriendo nuevas ramas del arbol.
        multisetActual = multisetActual->siguiente[pos];
    }
    multisetActual->cantidad = multisetActual->cantidad + 1;
    m->cantidad = m->cantidad + 1;
}

/**
 Devuelve la cantidad de repeticiones de la palabra s en el multiset m.
**/
int multiset_cantidad(multiset_t *m, char *s)
{
    int l = strlen(s);
    int i, pos;
    multiset_t* p = m;

    for(i = 0; i < l; i++)
    {
        pos = tolower(s[i]) - 'a';
        if(p->siguiente[pos] == NULL)
            return 0;
        p = p->siguiente[pos];
    }
    return p->cantidad;
}

/**
 Devuelve una lista de tipo lista t ordenada según la función f con todos los elementos del multiset m y la cantidad de apariciones de cada uno.
**/
lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t, elemento_t))
{
    lista_t* to_return = lista_crear();
    char palabra[50] = ""; //Asumimos que cuanto mucho la palabra va a tener 50 caracteres; la inicializamos con nulo.
    preorden(m, palabra, to_return);
    return *to_return;
}

/**
 Elimina el multiset m liberando el espacio de memoria reservado. Luego de la invocación m debe valer NULL.
**/
void multiset_eliminar(multiset_t **m)
{
    destruir(*m, destruir_elemento);
    *m = NULL;
}

// --------------------------------------------------

/**
  Realiza un recorrido en preorden del multiset m y guarda en una lista l las palabras formadas en el proceso.
    m: Puntero al multiset a recorrer en preorden.
    palabra: Puntero al arreglo de caracteres que representa la palabra en construcción.
    l: Puntero a una lista en la que se almacenarán las palabras obtenidas durante el recorrido.
*/
void preorden(multiset_t *m, char* palabra, lista_t* l)
{
    elemento_t elem;
    elem.a = m->cantidad;
    elem.b = palabra;

    if(m->cantidad > 0)
        lista_insertar(l, elem, 0);

    int i, longi;
    char c;

    for(i = 0; i < 26; i++)
    {
        if(m->siguiente[i] != NULL)
        {
            c = 'a' + i;
            longi = strlen(palabra);
            palabra[longi] = c;
            palabra[longi+1] = '\0';
            preorden(m->siguiente[i], palabra, l);
            palabra[longi] = '\0';
        }
    }
}

/**
  Destruye el multiset m y libera el espacio de memoria reservado.
    m: Puntero al multiset a destruir.
    destruir_elemento: Función que se utilizará para destruir cada elemento almacenado en el multiset.
*/
void destruir(multiset_t *m, void (*destruir_elemento)(void*))
{
    int i;
    if(m != NULL)
    {
        for(i = 0; i < 26; i++)
            destruir(m->siguiente[i], destruir_elemento);

        free(m);
    }
}

/**
  Libera la memoria asociada a un elemento.
    elemento: Puntero al elemento a destruir.
*/
void destruir_elemento(void* elemento)
{
    free(elemento);
}
