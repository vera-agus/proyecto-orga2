#include <stdio.h>
#include <stdlib.h>

#include "listaordenada.h"
// --> me tira error en compilación si no está comentado, pero no entiendo pq.
// "multiple definition of ..." todas las funciones.

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

// PROTOTIPOS DE FUNCIONES AUXILIARES

celda_t* merge(celda_t* a, celda_t* b, funcion_comparacion_t comparar);
int mergeSort(celda_t** p, funcion_comparacion_t comparar);
int dividir(celda_t* p, celda_t** ini, celda_t** fin);

// --------------------------------------------------------------

/**
 Inicializa una lista vacía.
**/
lista_t *lista_crear()
{
    lista_t *lista = (lista_t*) malloc(sizeof(struct lista));
    lista->primera = NULL;
    lista->cantidad = 0;
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
        celda_t *celdaAux= (celda_t*) malloc (sizeof(celda_t));
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
    elemento_t* elem_to_return;
    celda_t *celda= l->primera;
    if(l->cantidad >= pos)
    {
        int i;
        for(i= 0; i < pos; i++)
        {
            celda= celda->siguiente;
        }
        elem = celda->elem;
        elem_to_return = &elem;
        //elem = NULL;
        //free(elem); //es necesario? --> esto vi que hacíamos free cuando era puntero, podemos preguntarlo
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
    elemento_t* elem_to_return = NULL;
    celda_t *celda= l->primera;
    if(l->cantidad >= pos){
        int i;
        for(i= 0; i < pos; i++)
            {
            celda= celda->siguiente;
        }
        *elem_to_return = celda->elem;
        return elem_to_return;
    }
    else
        exit(LST_POS_INVALIDA);
}

/**
Dada la lista l y la función comparar ordena la lista de acuerdo al criterio de dicha función.
**/
int lista_ordenar(lista_t *l, funcion_comparacion_t comparar)
{
    void* p = &(l->primera);
    int to_return = mergeSort(p, comparar);
    return to_return;
}

/**
Devuelve la cantidad de elementos de la lista l.
**/
unsigned int lista_cantidad(lista_t *l)
{
    return l->cantidad; //considerando que cada celda tiene un elem.
}

/*
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
*/

/**
Devuelve verdadero (̸= 0) si la lista está vacía, y falso (= 0) si la lista contiene al menos un elemento.
**/
int lista_vacia(lista_t lista)
{
    if(lista.cantidad == 0)
        return TRUE;
    else
        return FALSE;
}

// --------------------------------------------------

celda_t* merge(celda_t* a, celda_t* b, funcion_comparacion_t comparar)
{
    celda_t* to_return = NULL;

    // Si una de las listas está vacía, la otra lista se devuelve
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if(comparar(&(a->elem), &(b->elem)))
    {
        to_return = a;
        to_return->siguiente = merge(a->siguiente, b, comparar);
    }
    else
    {
        to_return = b;
        to_return->siguiente = merge(a, b->siguiente, comparar);
    }

    return to_return;
}

int mergeSort(celda_t** p, funcion_comparacion_t comparar)
{
    celda_t* a;
    celda_t* b;

    // Si la lista está vacía o tiene un solo nodo, ya está ordenada
    if ((*p == NULL) || ((*p)->siguiente == NULL))
        return 0;

    // Dividimos la lista en dos mitades
    dividir(*p, &a, &b);

    // Ordenamos las dos mitades recursivamente con mergeSort
    mergeSort(&a, comparar);
    mergeSort(&b, comparar);

    // Unimos las dos mitades ordenadas con merge
    *p = merge(a, b, comparar);

    return 0;
}

int dividir(celda_t* p, celda_t** ini, celda_t** fin)
{
    // si la longitud es menor a 2, manejarlo por separado
    if (p == NULL || p->siguiente == NULL)
    {
        *ini = p;
        *fin = NULL;
        return 0;
    }

    celda_t* p1 = p;
    celda_t* p2 = p->siguiente; //este recorre dos lugares por cada uno de p1

    // avanzo dos por p2 y uno por p1
    while (p2 != NULL)
    {
        p2 = p2->siguiente;
        if (p2 != NULL)
        {
            p1 = p1->siguiente;
            p2 = p2->siguiente;
        }
    }

    //p1 está justo antes del punto medio de la lista; partimos acá.
    *ini = p;
    *fin = p1->siguiente;
    p1->siguiente = NULL;

    return 0;
}
