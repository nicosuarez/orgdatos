///////////////////////////////////////////////////////////
//  Space.cpp
//  Implementation of the Class Space
//  Created on:      13-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Space.h"


Space::Space(){

}



Space::~Space(){

}





/**
 * Obtener el path del archivo del cual pertenece el espacio.
 */
string Space::GetFilePath(){

	return  NULL;
}


/**
 * Obtiene el formato/extension del archivo.
 */
string Space::GetFormat(){

	return  NULL;
}


/**
 * Apunta al comienzo de la posicion del espacio dentro del archivo.
 */
int Space::GetInitialPosition(){

	return 0;
}


/**
 * Tamano total en bytes de lo que ocupa el espacio.
 */
int Space::GetSize(){

	return 0;
}