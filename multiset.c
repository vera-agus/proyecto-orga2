#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "multiset.h"

struct trie{
int cantidad; // Cantidad de veces que aparece esa palabra en el multiset
struct trie *siguiente[26];
}


