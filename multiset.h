#include <stdio.h>
#include <stdlib.h>
#include "define.h"

struct trie;
typedef struct trie multiset_t;

//Metodos de TDA multiset.
multiset_t *multiset crear();
void multiset_insertar(multiset_t *m, char *s)
int multiset_cantidad(multiset_t *m, char *s);
lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t,elemento_t)); 
void multiset_eliminar(multiset_t **m);
