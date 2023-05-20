#include <stdio.h>
#include <stdlib.h>
#include "listaordenada.c" //Me da errores si uso el Header

int main()
{
    //Verificamos funcionalidad.
    lista_t * prueba;
    prueba = lista_crear();
    elemento_t elem1;
    elem1.a = 1;
    elem1.b ="uno";
    elemento_t elem2;
    elem2.a = 2;
    elem2.b ="dos";
    elemento_t elem3;
    elem3.a = 3;
    elem3.b ="tres";
    elemento_t elem4;
    elem4.a = 4;
    elem4.b ="cuatro";
    lista_insertar(prueba, elem1, 0);
    lista_insertar(prueba, elem2, 1);
    lista_insertar(prueba, elem3, 2);
    lista_insertar(prueba, elem4, 3);
    printf("Elemento en la primera celda tiene como a y b: %i y %s\n", elem2.a , elem2.b);
    elemento_t *elemAux1;
    elemAux1= lista_eliminar(prueba, 1);
    //printf("Elemento en la primera celda tiene como a y b: %i y %s\n", elem1.a , elem1.b);
    printf("Elemento en la primera celda tiene como a y b: %i y %s\n", elemAux1->a , elemAux1->b);
    elemento_t *elemAux2= lista_elemento(prueba, 2);
    printf("Elemento en la primera celda tiene como a y b: %i y %s\n", elemAux2->a , elemAux2->b);

    return 0;
}

