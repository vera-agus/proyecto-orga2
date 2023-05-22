#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    lista_t * prueba;
    prueba = lista_crear();
    elemento_t elem1;
    elemento_t elem2;
    elemento_t elem3;
    elemento_t elem4;
    elemento_t elem5;
    elemento_t elem6;
    elem1.a = 1;
    elem1.b ="uno";
    elem2.a = 2;
    elem2.b ="dos";
    elem3.a = 3;
    elem3.b ="tres";
    elem4.a = 4;
    elem4.b ="cuatro";
    elem5.a = 3;
    elem5.b = "zanahoria";
    elem6.a = 3;
    elem6.b = "quince";
    lista_insertar(prueba, elem4, 0);
    lista_insertar(prueba, elem1, 1);
    lista_insertar(prueba, elem5, 2);
    lista_insertar(prueba, elem2, 3);
    lista_insertar(prueba, elem3, 4);
    lista_insertar(prueba, elem6, 5);

    for(int i = 0; i < lista_cantidad(prueba); i++)
        printf("%i %s\n", lista_elemento(prueba, i)->a, lista_elemento(prueba, i)->b);

    printf("\n");
    lista_ordenar(prueba, comparar);

    for(int i = 0; i < lista_cantidad(prueba); i++)
        printf("%i %s\n", lista_elemento(prueba, i)->a, lista_elemento(prueba, i)->b);
}
