#ifndef DEFINESFILES_H_
#define DEFINESFILES_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define bool unsigned int
#define TRUE  1
#define FALSE 0 

/* Modos de apertura de archivos */
#define READ                   1
#define WRITE                  2
#define READ_WRITE             3    /* READ | WRITE */
#define APPEND                 4

/* Valores devueltos por las primitivas */
#define     RES_OK                   0    /* La primitiva se ejecutó con éxito */
#define     RES_NULL                -1    /* No se pudo abrir el archivo */
#define     RES_ERROR               -2    /* Se produjo un error */
#define     RES_EOF                 -3    /* Fin de Archivo */
#define     RES_EXISTE              -4    /* El registro/archivo ya existe */
#define     RES_NO_EXISTE           -5    /* El registro no existe */
#define     RES_EXISTE_INDICE       -6    /* El índice ya existe */
#define     RES_NO_ EXISTE_INDICE   -7    /* El índice no existe */
#define     RES_ARCHIVO_LLENO       -8    /* El archivo directo está lleno */
#define     RES_ES_PRIM             -9    /* El índice que se intenta eliminar
                                                    es el principal */


/* Un registro o una clave se especifica como una sucesión de campos, que contienen
 * nombre de campo, tipo de campo y longitud del mismo, más un ultimo campo con nombre 0 ( null
 * pointer ).  
*/

typedef struct {
        const char* nombre;
        int    tipo;
        int    longitud;
}campo;

/* Valores con signo. */
#define CHAR                 1
#define INT                  2
#define LONG                 3
#define FLOAT                4
#define DOUBLE               5
#define UNSIGNED             0x80 /* para indicar valores sin signo se utiliza el operador |   (OR
a nivel de bits) por ejemplo, para indicar un campo de entero sin signo se utiliza UNSIGNED | INT
*/


#endif /*DEFINESFILES_H_*/
