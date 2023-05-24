#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "listaordenada.h"

typedef struct celda
{
    elemento_t *elem;
    struct celda *siguiente;
} c; // A la c la agregamos nosotros

// BEGIN - PROTOTIPOS DE FUNCIONES AUXILIARES
celda_t * merge(celda_t* a, celda_t* b, funcion_comparacion_t comparar);
int mergeSort(celda_t** p, funcion_comparacion_t comparar);
int dividir(celda_t* p, celda_t** ini, celda_t** fin);
// END - PROTOTIPOS DE FUNCIONES AUXILIARES

// --------------------------------------------------------------

/**
 Inicializa una lista vacía y la retorna.
**/
lista_t * lista_crear()
{
    lista_t * lista = (lista_t *) malloc(sizeof(lista_t));
    lista->primera = NULL;
    lista->cantidad = 0;
    return lista;
};

/**
 Inserta el elemento elem en la posición pos de la lista.
 Asumimos:
    Se crea una nueva celda con el elemento dentro, y se asigna en la posicion ingresada.
    La primer posicion en la lista es 0.
    La posicion ingresada debe estar en el rango de 0 a l->cant.
**/
int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos)
{
    if (pos > l->cantidad)
       exit(LST_POS_INVALIDA);
    //deberiamos verificar si el elemento pasado por parametro no tenga a o b nulos.
    celda_t *nueva_celda = (celda_t*)malloc(sizeof(struct celda)); //Luego deberia ser liberado en el Eliminar.
    elemento_t *elemento = (elemento_t*)malloc(sizeof(struct elemento));
    elemento->b = (char*)malloc(strlen(elem.b) + 1);
    elemento->a = elem.a;
    strcpy(elemento->b, elem.b);
    nueva_celda->elem = elemento;
    if(pos == 0) //posicion es igual a 0.
    {
        nueva_celda->siguiente= l->primera;
        l->primera= nueva_celda;
    }
    else if (l->cantidad > pos){ //posicion mayor a 0 pero menos a l->cant.
        int i;
        celda_t *celda_anterior= NULL;
        celda_t *celda_actual= l->primera;
        for(i= 0; i < pos; i++)
        {
            celda_anterior= celda_actual;
            celda_actual= celda_actual->siguiente;
        }
        nueva_celda->siguiente= celda_actual; //Inseramos la nueva celda dentras de celda actual, que esta ultima.
        celda_anterior->siguiente= nueva_celda; //Insertamos la nueva celda siguente de celda anterior.
    }
    else if (l->cantidad == pos){//Cuando la posiscion es la ultima
        int i;
        celda_t *celda_anterior= NULL;
        celda_t *celda_actual= l->primera;
        for(i= 0; i < pos; i++)
        {
            celda_anterior= celda_actual;
            celda_actual= celda_actual->siguiente;
        }
        celda_anterior->siguiente= nueva_celda;
        nueva_celda->siguiente= NULL;
    }
    l->cantidad++;

    return 0;
}

/**
Elimina el elemento de la posición pos de la lista.
**/
elemento_t * lista_eliminar(lista_t* l, unsigned int pos) {
    if (l == NULL || l->primera == NULL || pos > l->cantidad) {
        exit(LST_POS_INVALIDA); // Si la posición está fuera de los límites de la lista.
    }
    celda_t* actual = l->primera;
    celda_t* anterior = NULL;
    elemento_t * toReturn= NULL;
    // Buscamos la celda correspondiente a la posición a eliminar
    int i;
    for (i = 0; i < pos; i++) {
        printf("holaa");
        anterior = actual;
        actual = actual->siguiente;
    }
    if (anterior == NULL) {
        // Si la celda a eliminar es la primera de la lista
        l->primera = actual->siguiente;
    } else {
        // Si la celda a eliminar está en medio o al final de la lista
        anterior->siguiente = actual->siguiente;
    }
    printf("holis");
    toReturn = (actual->elem);
    toReturn->a= (actual->elem->a);
    toReturn->b= (actual->elem->b);
    free(actual->elem);
    free(actual); // Liberamos la memoria de la celda eliminada, PERDEMOS LA DIRECCION AL ELEMENTO.
    printf("chau");
    l->cantidad--; // Actualizamos la cantidad de elementos de la lista
    return toReturn;
}

/**
 Devuelve un puntero al elemento que ocupa la posición pos de la lista.
**/
elemento_t *lista_elemento(lista_t *l, unsigned int pos)
{
    if(pos > l->cantidad)
        exit(LST_POS_INVALIDA);
    elemento_t* elem_to_return = NULL;
    celda_t *celda= l->primera;
    if(l->cantidad >= pos){
        int i;
        for(i= 0; i < pos; i++)
        {
            celda= celda->siguiente;
        }
        elem_to_return = (celda->elem);
    }
    return elem_to_return;
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

/**
  Realiza merge de dos listas enlazadas a y b, ordenando los elementos en función de un criterio de comparación proporcionado.
    a: Puntero a la cabeza de la primera lista enlazada.
    b: Puntero a la cabeza de la segunda lista enlazada.
    comparar: Función de comparación que compara dos elementos y devuelve un valor que indica la relación de orden entre ellos.
  Retorna un puntero a la cabeza de la lista enlazada resultante de aplicar merge.
*/
celda_t* merge(celda_t* a, celda_t* b, funcion_comparacion_t comparar)
{
    celda_t* to_return = NULL;

    // Si una de las listas está vacía, la otra lista se devuelve
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if(comparar((a->elem), (b->elem)) == ELEM1_MENOR_QUE_ELEM2)
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

/**
  Realiza el merge sort en una lista, utilizando la función de comparación para comparar los elementos. Ordena la lista en su lugar, reordenando los punteros.
    p: Puntero a un puntero a la cabeza de la lista enlazada a ordenar.
    comparar: Función de comparación que compara dos elementos y devuelve un valor que indica la relación de orden entre ellos.
  Retorna un entero que indica el éxito del proceso de ordenamiento.
*/
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

/**
  Divide una lista en dos mitades, utilizando merge sort. Actualiza los punteros ini y fin para señalar el inicio y el final de las mitades divididas.
    p: Puntero a la cabeza de la lista enlazada a dividir.
    ini: Puntero a un puntero para almacenar la cabeza de la primera mitad dividida.
    fin: Puntero a un puntero para almacenar la cabeza de la segunda mitad dividida.
  Retorna un entero que indica el éxito o error del proceso de división.
*/
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
