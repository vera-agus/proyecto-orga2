#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiset.h"
#include "listaordenada.h"

comparacion_resultado_t comparar(struct elemento* e1, struct elemento* e2) //¿ e1 < e2 ?
{
    printf("%i %s\n", e1->a, e1->b);
    int toReturn = e1->a == e2->a;
    if(toReturn == 1) //e1->a es igual que e2->a
    {
        toReturn = strcmp(e1->b, e2->b);
        if(toReturn == 1)
            toReturn = 0;
    }
    else
    {
        toReturn = e1->a < e2->a;
    }
    return toReturn;
};

int comparar_multiset(elemento_t e1, elemento_t e2)
{
    return comparar(&e1, &e2);
}

int main()
{
    multiset_t* m = multiset_crear(); // OK - Finaliza con 0
    char* p1 = "uno";
    char* p2 = "dos";
    char* p3 = "tres";
    char* p4 = "cuatro";
    char* p5 = "cinco";
    char* un = "un";

    // int cant1, cant2, cant3, cant4, cant5, cantUN;

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
    multiset_insertar(m, p5);
    multiset_insertar(m, un); // OK - Finaliza con 0

    /*
    cant1 = multiset_cantidad(m, p1);
    cant2 = multiset_cantidad(m, p2);
    cant3 = multiset_cantidad(m, p3);
    cant4 = multiset_cantidad(m, p4);
    cant5 = multiset_cantidad(m, p5);
    cantUN = multiset_cantidad(m, un); // OK - Finaliza con 0 y computa bien

    printf("p1 aparece %i veces, \np2 aparece %i veces, \np3 aparece %i veces, \np4 aparece %i veces, \np5 aparece %i veces \n\n", cant1, cant2, cant3, cant4, cant5);
    */

    lista_t l = multiset_elementos(m, comparar_multiset);
    int cant = lista_cantidad(&l);
    printf("\n");
    for(int i = 0; i < cant; i++)
        printf("%i %s\n", lista_elemento(&l, i)->a, lista_elemento(&l, i)->b);
    printf("\n");

    multiset_eliminar(&m); // OK - Finaliza con 0 y setea a m en NULL

    if(m == NULL)
        printf("borra OK");

    return 0;

    /*
    //TEST CON MULTISET D: POR QUE NO ANDÁAAAAAAAAAAAAA
    multiset_t* m = multiset_crear(); // OK - Finaliza con 0
    char* p1 = "uno";
    char* p2 = "dos";
    char* p3 = "tres";
    char* p4 = "dos";
    char* p5 = "uno";

    char* p6 = "dos";
    char* p7 = "treinta";
    char* p8 = "tres";
    char* p9 = "treinta";

    char* p10 = "tres";
    char* p11 = "doce";
    char* p12 = "treinta";
    char* p13 = "treinta";
    char* p14 = "ocho";

    char* p15 = "dos";
    char* p16 = "treinta";
    char* p17 = "ocho";
    char* p18 = "ocho";


    // int cant1, cant2, cant3, cant4, cant5, cantUN;

    multiset_insertar(m, p1);
    multiset_insertar(m, p2);
    multiset_insertar(m, p3);
    multiset_insertar(m, p4);
    multiset_insertar(m, p5);
    multiset_insertar(m, p6);
    multiset_insertar(m, p7);
    multiset_insertar(m, p8);
    multiset_insertar(m, p9);
    multiset_insertar(m, p10);
    multiset_insertar(m, p11);
    multiset_insertar(m, p12);
    multiset_insertar(m, p13);
    multiset_insertar(m, p14);
    multiset_insertar(m, p15);
    multiset_insertar(m, p16);
    multiset_insertar(m, p17);
    multiset_insertar(m, p18);

    /*
    cant1 = multiset_cantidad(m, p1);
    cant2 = multiset_cantidad(m, p2);
    cant3 = multiset_cantidad(m, p3);
    cant4 = multiset_cantidad(m, p4);
    cant5 = multiset_cantidad(m, p5);
    cantUN = multiset_cantidad(m, un); // OK - Finaliza con 0 y computa bien

    printf("p1 aparece %i veces, \np2 aparece %i veces, \np3 aparece %i veces, \np4 aparece %i veces, \np5 aparece %i veces \n\n", cant1, cant2, cant3, cant4, cant5);
    */

    lista_t l = multiset_elementos(m, comparar_multiset);
    int cant = lista_cantidad(&l);
    printf("\n");
    for(int i = 0; i < cant; i++)
        printf("%i %s\n", lista_elemento(&l, i)->a, lista_elemento(&l, i)->b);
    printf("\n");

    multiset_eliminar(&m); // OK - Finaliza con 0 y setea a m en NULL

    if(m == NULL)
        printf("borra OK");

    return 0;
    */
}