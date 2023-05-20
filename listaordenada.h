

struct elemento
{
    int a;
    char *b;
};

//Structs para la manipulación de la lista
typedef struct elemento elemento_t;

typedef enum
{
  ELEM1_MAYOR_QUE_ELEM2,
  ELEM1_IGUAL_QUE_ELEM2,
  ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;


typedef comparacion_resultado_t (funcion_comparacion_t) ( //compara elem->b de cada elem, ordenandolos de menor a mayor.
    elemento_t *elem1, elemento_t *elem2                  // si elem->b es igual compara los strings (elem->a).
); //implementamos en el main.

typedef struct celda celda_t;

struct lista
{
    celda_t *primera; //puntero a la primera celda de la lista
    int cantidad; // cantidad de elementos de la lista
};

typedef struct lista lista_t; //struct lista == lista_t

// ---------------------------------------------------------------------------------------------
// Definición de prototipos y documentación de las funciones.
// ---------------------------------------------------------------------------------------------

//Metodos TDA lista.

/**
 Crea una lista vacía y la devuelve.
**/
extern lista_t * lista_crear();

/**
 Inserta el elemento elem en la posición pos de la lista.
**/
extern int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos);

/**
Elimina el elemento de la posición pos de la lista.
**/
extern elemento_t *lista_eliminar(lista_t *l, unsigned int pos);

/**
 Devuelve un puntero al elemento que ocupa la posición pos de la lista.
**/
extern elemento_t *lista_elemento(lista_t *l, unsigned int pos);

/**
Dada la lista l y la función comparar ordena la lista de acuerdo al criterio de dicha función.
**/
extern int lista_ordenar(lista_t *l, funcion_comparacion_t comparar);

/**
Devuelve la cantidad de elementos de la lista l.
**/
extern unsigned int lista_cantidad(lista_t *l);

/**
Devuelve verdadero (̸= 0) si la lista está vacía, y falso (= 0) si la lista contiene al menos un elemento.
**/
extern int lista_vacia(lista_t lista);


