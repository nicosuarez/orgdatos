///////////////////////////////////////////////////////////
//  Space.cpp
//  Implementation of the Class Space
//  Created on:      13-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Space.h"


Space::Space(string filePath, string format, long initialPosition, long size)
{
	this->filePath = filePath;
	this->format = format;
	this->initialPosition = initialPosition;
	this->size = size;
}

Space::Space(string filePath)
{
	this->filePath = filePath;
	this->format = "";
	this->initialPosition = 0;
	this->size = 0;
}


Space::~Space(){

}


/**
 * Obtener el path del archivo del cual pertenece el espacio.
 */
const char* Space::GetFilePath() const
{
	return  this->filePath.c_str();
}


/**
 * Obtiene el formato/extension del archivo.
 */
string Space::GetFormat() const
{
	return  this->format;
}


/**
 * Apunta al comienzo de la posicion del espacio dentro del archivo.
 */
long Space::GetInitialPosition() const 
{
	return this->initialPosition;
}


/**
 * Tamano total en bytes de lo que ocupa el espacio.
 */
long Space::GetSize() const
{
	return this->size;
}
