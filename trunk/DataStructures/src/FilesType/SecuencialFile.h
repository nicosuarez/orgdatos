#ifndef SECUENCIALFILE_
#define SECUENCIALFILE_

#include "DefinesFiles.h"

/* Se crea un archivo secuencial. 
 * Retorno: RES_OK,RES_ERROR,RES_EXISTE */ 
int S_CREATE(const char* nombre);

/* Abre un archivo secuencial. 
 * Retorno: Devuelve el file handler si puede abrir el archivo o RES_NULL si no. 
 * Los valores posibles para el parámetro modo son en este caso READ que abre el
 * archivo ( previamente creado ) y se posiciona en el primer registro ( en este
 *  modo las llamadas S_WRITE devuelven RES_ERROR), y APPEND que se posiciona al 
 * final del archivo ( en este modo las llamadas a S_READ devuelven RES_ERROR ).
 */ 
int S_OPEN(const char* nombre, int modo);

/* Cierra un archivo secuencial previamente abierto. 
 * Retorno: RES_OK,RES_ERROR*/ 
int S_CLOSE(int fhandler);

/* Lee a partir de la posición indicada por el record pointer y avanza dicho 
 * puntero a la posición siguiente a la última que lee.
 * Retorno: RES_OK,RES_ERROR,RES_EOF */ 
int S_READ(int fhandler, void* reg);

/* Se puede agregar sólo al final del archivo. El parámetro cant se utiliza 
 * para indicar la longitud de reg. Toma los datos de reg (tantos bytes 
 * como indique cant), si se utiliza un caracter de fin de registro, si
 * dentro de estos datos apareciera un carácter especial ( de escapeo o 
 * fin de registro) lo expande, agrega un caracter de fin de registro al 
 * final de los datos y por último escribe al archivo. Si se utiliza la 
 * técnica de almacenar la longitud de registro, escribe al archivo la 
 * longitud indicada por cant y luego escribe los datos al archivo.
 * Retorno: Devuelve un código de resultado(RES_OK / RES_ERROR).*/
int S_WRITE(int fhandler, const void* reg, unsigned long cant);


#endif /*SECUENCIALFILE_*/
