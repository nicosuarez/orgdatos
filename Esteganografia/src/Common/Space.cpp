///////////////////////////////////////////////////////////
//  Space.cpp
//  Implementation of the Class Space
//  Created on:      13-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Space.h"


Space::Space(ID_type idSpace, ID_type idImg , string filePath, unsigned long initialPosition, unsigned long size)
{
	this->filePath = filePath;
	this->format = "";
	this->initialPosition = initialPosition;
	this->size = size;
	this->idSpace = idSpace;
	this->idImg = idImg;
}

Space::Space( ID_type idImg, string filePath, unsigned long initialPosition, unsigned long size )
{
	this->filePath = filePath;
	this->format = "";
	this->initialPosition = initialPosition;
	this->size = size;
	this->idSpace = 0;
	this->idImg = idImg;
}


Space::Space(ID_type idSpace, ID_type idImg, unsigned long size)
{
	this->filePath = "";
	this->format = "";
	this->initialPosition = 0;
	this->size = size;
	this->idImg = idImg;
	this->idSpace = idSpace;
}

Space::Space(string filePath, string format, unsigned long initialPosition, unsigned long size)
{
	this->filePath = filePath;
	this->format = format;
	this->initialPosition = initialPosition;
	this->size = size;
	this->idSpace = 0;
}

Space::Space(string filePath, unsigned long initialPosition, unsigned long size)
{
	this->filePath = filePath;
	this->initialPosition = initialPosition;
	this->size = size;
	this->idSpace = 0;
}

Space::Space(ID_type idImg, unsigned long initialPosition, unsigned long size)
{
	this->idImg = idImg;
	this->initialPosition = initialPosition;
	this->size = size;
	this->idSpace = 0;
}

Space::Space(ID_type idSpace, ID_type idImg, unsigned long initialPosition, unsigned long size)
{
	this->idImg = idImg;
	this->initialPosition = initialPosition;
	this->size = size;
	this->idSpace = idSpace;
}

Space::Space(string filePath)
{
	this->filePath = filePath;
	this->format = "";
	this->initialPosition = 0;
	this->size = 0;
	this->idSpace = 0;
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
unsigned long Space::GetInitialPosition() const 
{
	return this->initialPosition;
}


/**
 * Tamano total en bytes del archivo donde esta contenido el espacio.
 */
unsigned long Space::GetTotalSize() const
{
	unsigned long pos = 0;
	std::ifstream fin(this->filePath.c_str());
	if(fin)
	{
	   fin.seekg(0, std::ios::end); 
	   pos = fin.tellg();
	}
	fin.close();
	return pos;
}

/**
 * Tamano total en bytes de lo que ocupa el espacio en el archivo.
 */
unsigned long Space::GetSize() const
{
	return this->size;
}

/**
 * Tamano total en bytes de lo que ocupa el espacio en el archivo.
 */
void Space::SetSize(unsigned long size)
{
	this->size = size;
}

/**
 * Apunta al comienzo de la posicion del espacio dentro del archivo.
 */
void Space::SetInitialPosition(unsigned long position)
{
	this->initialPosition = position;
}

/*
 * Devuelve el id de la imagen a la que pertenece el space
 */
ID_type Space::GetIDImage() const
{
	return this->idImg;
}

/*
 * Setea el id de la imagen a la que pertenece el space
 */
void Space::SetIDImage(ID_type idImg)
{
	this->idImg = idImg;
}

/*
 * Devuelve el id del espacio.
 */
ID_type Space::GetIDSpace() const
{
	return idSpace;
}

/*
 * Setea el id al espacio
 */
void Space::SetIDSpace(ID_type spaceId)
{
	this->idSpace = spaceId;
}


