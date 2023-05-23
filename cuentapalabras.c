#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "listaordenada.h"
#include "multiset.h"
#define MAX_BUF 200

/**
 Compara los elementos e1 y e2 y retorna si e1 es mayor, igual o menor que e2 seg�n el valor de sus atributo a y, de ser necesario, b.
*/
comparacion_resultado_t comparar(struct elemento* e1, struct elemento* e2) //� e1 < e2 ?
{
    int valorComparacion = e1->a == e2->a;
    comparacion_resultado_t toReturn;
    if(valorComparacion == 1) //e1->a es igual que e2->a
    {
        valorComparacion = strcmp(e1->b, e2->b);
        if(valorComparacion == 0)
            toReturn = ELEM1_IGUAL_QUE_ELEM2;
        else if(valorComparacion == -1)
            toReturn = ELEM1_MENOR_QUE_ELEM2;
        else
            toReturn = ELEM1_MAYOR_QUE_ELEM2;
    }
    else
    {
        valorComparacion = e1->a < e2->a;
        if(valorComparacion == 0)
            toReturn = ELEM1_MAYOR_QUE_ELEM2;
        else
            toReturn = ELEM1_MENOR_QUE_ELEM2;
    }
    return toReturn;
};

int comparar_multiset(elemento_t e1, elemento_t e2)
{
    return comparar(&e1, &e2);
};

void cada_uno(multiset_t* mArchivo, char* nombreArchivo) //Imprime el orden de los archivos al rev�s
{
    FILE *cadauno = fopen("cadauno.txt", "a+");
    lista_t l = multiset_elementos(mArchivo, comparar_multiset);
    int i, cantidad;
    cantidad = lista_cantidad(&l);
    int aAux;
    char* bAux;

    fprintf(cadauno, "%s\n", nombreArchivo);

    for(i = 0; i < cantidad - 1; i++) //Hasta cantidad porque sino incluye la cantidad total de elementos del multiset y no corresponde
    {
        aAux = lista_elemento(&l, i)->a;
        bAux = lista_elemento(&l, i)->b;
        fprintf(cadauno, "%i   %s\n", aAux, bAux);
    }

    fclose(cadauno);
    // Liberar espacio de la lista
}

void totales(multiset_t* mTodos) //OK
{
    FILE *totales = fopen("totales.txt", "w+");
    lista_t l = multiset_elementos(mTodos, comparar_multiset);
    int i, cantidad;
    cantidad = lista_cantidad(&l);
    int aAux;
    char* bAux;

    for(i = 0; i < cantidad - 1; i++) //Hasta cantidad porque sino incluye la cantidad total de elementos del multiset y no corresponde
    {
        aAux = lista_elemento(&l, i)->a;
        bAux = lista_elemento(&l, i)->b;
        fprintf(totales, "%i   %s\n", aAux, bAux);
    }

    fclose(totales);
    // Liberar espacio de la lista
}


multiset_t* procesamiento_archivo(char* rutaDirectorio, char* nombreArchivo, multiset_t* mTodos) //OK
{
    char linea[100] = "\0";
    char rutaArchivo[200];

    printf("%s\n", nombreArchivo);
    snprintf(rutaArchivo, sizeof(rutaArchivo), "%s\\%s", rutaDirectorio, nombreArchivo); //Hace un append al path del directorio con el nombre del archivo

    FILE *f = fopen(rutaArchivo, "r");

    multiset_t* m = multiset_crear(); //En este multiset vamos a guardar todas las apariciones del archivo parametrizado.

    while(!feof(f))
    {
        fscanf(f,"%s", linea);
        multiset_insertar(m, linea);
        multiset_insertar(mTodos, linea);
    }

    fclose(f);

    return m;
}

lista_t* abrir_directorio(char* cadena) //OK
{
  DIR *dir;
  struct dirent *ent;
  lista_t* lista = lista_crear();
  int i = 0;
  int cantidad;
  int error = 0;

  dir = opendir (cadena);

  if (dir != NULL)
  {
    ent = readdir (dir);
    while (ent!= NULL)
    {       // Verifica que el archivo a procesar no es invalido
        if ((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0))
        {
            elemento_t elem = {i, ent->d_name};
            error = lista_insertar(lista, elem, i);
        }
        ent = readdir (dir);
    }
    closedir (dir);

    if(error != 0)
    {
        cantidad = lista_cantidad(lista);
        for(i = 0; i < cantidad; i++)
            lista_eliminar(lista, 0);
        free(lista);
        lista = NULL;
    }
    return lista;
  }
  else
  {
    perror("No se pudo acceder al directorio");
    return NULL;
  }
}

int main()
{
    char* pathDirectorio = "C:\\Users\\mlpro\\OneDrive\\Documentos\\Universidad\\Computaci�n\\Cursado actual\\Organizaci�n de Computadoras\\C�digo\\proyecto-orga2\\Dir";
    lista_t* archivos = abrir_directorio(pathDirectorio);
    multiset_t* mTodos = multiset_crear();
    multiset_t* m;
    char* nombreArchivo;
    int i;

    for(i = 0; archivos != NULL && i < lista_cantidad(archivos); i++)
    {
        nombreArchivo = lista_elemento(archivos, i)->b;
        m = procesamiento_archivo(pathDirectorio, nombreArchivo, mTodos);
        cada_uno(m, nombreArchivo);
        multiset_eliminar(&m);
    }

    lista_t l = multiset_elementos(mTodos, comparar_multiset);
    for(int j = 0; j < lista_cantidad(&l) - 1; j++)
        printf("%i %s: %i \n", lista_elemento(&l, j)->a, lista_elemento(&l, j)->b, j);

    totales(mTodos);
    multiset_eliminar(&mTodos);
    // Liberar espacio de la lista
}