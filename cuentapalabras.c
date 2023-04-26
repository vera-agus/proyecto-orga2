#include "listaordenada.h"
#include "multiset.h"

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

// Definición de macro de error para manejar errores en la apertura de archivos.
#define ARCH_ERROR_APERTURA -1
#define ERROR_MEMORIA       -2

// -----------------------------------------------------------------------------
/**
 Robado del proyecto de 2020; la consigna era contar la cantidad de apariciones de una palabra de un archivo de texto.
 - Cantidad apariciones: permite ingresar una palabra y muestra la cantidad de veces que dicha palabra se encuentra en el archivo.

--> No es igual, pero podemos robar bastante. Lee un archivo y carga las palabras a un mapeo; podemos adecuarlo a nuestros TDA.
**/

int procesamiento_archivo(char* ruta) //Adecuar según funcionalidades pedidas
{
    FILE *f = fopen(ruta, "r");
    char *puntero, *linea, *palabra;
    char *contenido_separado;

    multiset_t* m = multiset_crear();

    while(!EOF)
    {
        puntero = fgets(linea, 100, f);
        contenido_separado = strtok(puntero, " ");
        while(contenido_separado != NULL)
        {
            palabra = strdup(contenido_separado);

            if(palabra==NULL)
                return ERROR_MEMORIA;

            multiset_insertar(m, palabra);
            contenido_separado = strtok(NULL, " ");
        }
    }

    fclose(f);

    return 0;
}

/*
    robado de (fuente: de los deseos)

    https://poesiabinaria.net/2011/09/listar-archivos-dentro-de-un-directorio-o-carpeta-en-c/
*/

int main()
{
    DIR *dir;
    dir = opendir ("."); //. para abrir el directorio actual, cambiarlo por ruta variable ingresada x usuario

    if(dir == NULL) //¿¿¿¿modelar error????
        return ARCH_ERROR_APERTURA;

    struct dirent *ent; //guarda la info del archivo que se saca a cada momento

    while ((ent = readdir (dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0)) //comparamos los nombres de los archivos; si no nos dan . o .., es apto para abrir y no nos anda paseando por el directorio
            procesamiento_archivo(ent->d_name);
    }

    closedir(dir);

    return 0;
}
