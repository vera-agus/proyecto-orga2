#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiset.h"
#include "listaordenada.h"

comparacion_resultado_t comparar(struct elemento* e1, struct elemento* e2) //¿ e1 < e2 ?
{
    int toReturn = e1->a == e2->a;
    if(toReturn == 1) //e1->a es igual que e2->a
    {
        toReturn = strcmp(e1->b, e2->b);
        if(toReturn == 1)
            toReturn = 0;
    }
    else
        toReturn = e1->a < e2->a;
    return toReturn;
};

int main()
{
    multiset_t* m = multiset_crear(); // OK - Finaliza con 0
    char* p1 = "uno";
    char* p2 = "dos";
    char* p3 = "tres";
    char* p4 = "cuatro";
    char* p5 = "cinco";

    int cant1, cant2, cant3, cant4, cant5;

    multiset_insertar(m, p1);
    multiset_insertar(m, p1);
    multiset_insertar(m, p2);
    multiset_insertar(m, p3);
    multiset_insertar(m, p4);
    multiset_insertar(m, p4);
    multiset_insertar(m, p4);
    multiset_insertar(m, p5);
    multiset_insertar(m, p5);
    multiset_insertar(m, p5);
    multiset_insertar(m, p5); // OK - Finaliza con 0

    cant1 = multiset_cantidad(m, p1);
    cant2 = multiset_cantidad(m, p2);
    cant3 = multiset_cantidad(m, p3);
    cant4 = multiset_cantidad(m, p4);
    cant5 = multiset_cantidad(m, p5); // OK - Finaliza con 0 y computa bien

    printf("p1 aparece %i veces, \np2 aparece %i veces, \np3 aparece %i veces, \np4 aparece %i veces, \np5 aparece %i veces \n\n", cant1, cant2, cant3, cant4, cant5);

    lista_t l = multiset_elementos(m, comparar);
    int cant = lista_cantidad(&l);
    for(int i = 0; i < cant; i++)
        printf("%i %s\n", lista_elemento(&l, i)->a, lista_elemento(&l, i)->b);
    printf("\n");

    multiset_eliminar(&m); // OK - Finaliza con 0 y setea a m en NULL

    if(m == NULL)
        printf("borra OK");

    return 0;
}
