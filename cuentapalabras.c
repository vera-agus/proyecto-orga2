#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "listaordenada.h"
#include "multiset.h"
#define MAX_BUF 200

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
};

void cada_uno(multiset_t* mArchivo, char* nombreArchivo)
{
    FILE *cadauno = fopen("cadauno.out", "a+");
    lista_t l = multiset_elementos(mArchivo, NULL); //Cambiar NULL por la función de comparación
    int i, cantidad;
    cantidad = lista_cantidad(&l);
    int aAux;
    char* bAux;

    fprintf(cadauno, "%s", nombreArchivo);

    for(i = 0; i < cantidad; i++)
    {
        aAux = lista_elemento(&l, i)->a;
        bAux = lista_elemento(&l, i)->b;
        fprintf(cadauno, "%i   %s", aAux, bAux);
    }

    fclose(cadauno);
}

void totales(multiset_t* mTodos)
{
    FILE *totales = fopen("totales.out", "a+");
    lista_t l = multiset_elementos(mTodos, NULL); //Cambiar NULL por la función de comparación
    int i, cantidad;
    cantidad = lista_cantidad(&l);
    int aAux;
    char* bAux;

    for(i = 0; i < cantidad; i++)
    {
        aAux = lista_elemento(&l, i)->a;
        bAux = lista_elemento(&l, i)->b;
        fprintf(totales, "%i   %s", aAux, bAux);
    }

    fclose(totales);
}

multiset_t* procesamiento_archivo(char* ruta, multiset_t* mTodos) //No testeé individual, me lo robé de mi TPB
{
    char linea[100] = "\0";
    char *puntero;
    FILE *f = fopen(ruta, "r");

    multiset_t* m = multiset_crear(); //En este multiset vamos a guardar todas las apariciones del archivo parametrizado.

    while(puntero != NULL)
    {
        multiset_insertar(m, linea);
        multiset_insertar(mTodos, linea);
        puntero = fgets(linea,100,f);
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
    lista_t* archivos = abrir_directorio("C:\\Users\\mlpro\\Downloads\\Dir");
    multiset_t* mTodos = multiset_crear();
    multiset_t* m;
    char* nombreArchivo;

    for(int i = 0; archivos != NULL && i < lista_cantidad(archivos); i++)
    {
        nombreArchivo = lista_elemento(archivos, i)->b;
        m = procesamiento_archivo(nombreArchivo, mTodos);
        cada_uno(m, nombreArchivo);
    }

    totales(mTodos);
}
