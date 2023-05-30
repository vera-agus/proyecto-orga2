#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "listaordenada.h"
#include "multiset.h"
#define MAX_BUF 60

// BEGIN - Prototipos de funciones
comparacion_resultado_t comparar(struct elemento* e1, struct elemento* e2);
int comparar_multiset(elemento_t e1, elemento_t e2);
void cada_uno(multiset_t* mArchivo, char* nombreArchivo);
void totales(multiset_t* mTodos);
multiset_t* procesamiento_archivo(char* rutaDirectorio, char* nombreArchivo, multiset_t* mTodos);
lista_t* abrir_directorio(char* cadena);
void printGuiones();
void eliminarLista(lista_t* lista);
// END - Prototipos de funciones

int main(int argc, char* argv[])
{
    char opcion;

    //argc == 1 implica que no se incluye ningún otro parámetro más allá de la invocación del programa
    if(argc == 1 || (argc == 2 && strcmp(argv[1], "-h") == 0))
    {
        printf("Bienvenido a cuentapalabras!\n\n");

        printf("Este es un programa que le permitira contabilizar la cantidad de palabras contenidas en los archivos ");
        printf("de texto de un directorio especificado.\n");

        printf("A partir de la lectura de cada uno de los archivos de texto alojados en el directorio, se crearan otros ");
        printf("con el fin de que pueda determinar la cantidad total de veces que se encuentra cada palabra ");
        printf("(en total y por cada uno de los archivos).\n\n");

        printf("Si desea mayor informacion sobre las opciones disponibles presione Y, caso contrario presione N\n");
        printf("Y/N: ");
        scanf("%[^\n]", &opcion);

        if(opcion == 'y' || opcion == 'Y')
        {
            printf("\nESPECIFICACIONES SOBRE TOTALES\n\n");

            printf("A partir del directorio que proporcione, considerando los archivos de texto que el mismo contenga, ");
            printf("se creara un nuevo archivo conteniendo todas las palabras existentes entre los archivos y, ");
            printf("el nuevo archivo, contendra dichas palabras con la cantidad de apariciones totales entre todos ");
            printf("todos los archivos de texto que existen en la carpeta.\n");
            printf("Las palabras y sus respectivas cantidades se encuentran ordenadas segun la cantidad de apariciones.\n");

            printf("\nESPECIFICACIONES SOBRE CADA UNO\n\n");

            printf("A partir del directorio que proporcione, considerando los archivos de texto que el mismo contenga, ");
            printf("se creara un nuevo archivo conteniendo la cantidad de veces que aparece cada palabra en cada ");
            printf("uno de los archivos.\n");
            printf("Las palabras y sus respectivas cantidades se encuentran ordenadas segun la cantidad de apariciones.\n");
        }
        printf("\nEsperamos que la ayuda le haya sido de utilidad.\nHasta pronto!\n");
    }
    else
    {
        char* pathDirectorio = argv[1];
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

        totales(mTodos);
        multiset_eliminar(&mTodos);
        // Liberar espacio de la lista de archivos
        eliminarLista(archivos);
    }

    return 0;
}

/**
 Compara los elementos e1 y e2 y retorna si e1 es mayor, igual o menor que e2 según el valor de sus atributo a y, de ser necesario, b.
*/
comparacion_resultado_t comparar(struct elemento* e1, struct elemento* e2) //¿ e1 < e2 ?
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

void cada_uno(multiset_t* mArchivo, char* nombreArchivo) //OK
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
    eliminarLista(&l);
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
    if(f == NULL)
        exit(ARCH_ERROR_APERTURA);

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
            i = i+1;
        }
        ent = readdir (dir);
    }
    closedir (dir);

    if(error != 0)
    {
        /*)
        cantidad = lista_cantidad(lista);
        for(i = 0; i < cantidad; i++)
            lista_eliminar(lista, 0);
        free(lista);
        lista = NULL;
        */
        eliminarLista(lista);
    }
    return lista;
  }
  else
  {
    perror("No se pudo acceder al directorio");
    exit(DIR_ERROR_APERTURA);
  }
}

void eliminarLista(lista_t* lista)
{
    int cantidad = lista_cantidad(lista);
    int i;
    elemento_t* elementoEliminado;

    for(i = 0; i < cantidad; i++)
    {
        elementoEliminado = lista_eliminar(lista, 0);
        free(elementoEliminado);
    }

    free(lista);
    lista = NULL;
}