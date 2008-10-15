///////////////////////////////////////////////////////////
//  Bmp.cpp
//  Implementation of the Class Bmp
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Bmp.h"

using namespace std;

Bmp::Bmp(){

}

Bmp::~Bmp(){

}


/**
 * Implementar el comportamiento para extraer la informacion en un lugar
 * determinado.
 */
void Bmp::Extract(Space& space, Message& msg)
{

}

bool Bmp::ValidateFormat(Space space)
{
	fstream fin(space.GetFilePath());
	string format;
	string header("BM");
	bool isValid = false;
    
	if(fin.good())
	{
		fin >> format;
		if(format.compare(0,2,header) == 0)
			isValid = true;
	}
	else
	{
		cerr << "Error al abrir el archivo BMP." << space.GetFilePath() <<"\n";
	}
	
	if(!isValid)
		cerr << "Formato BMP incorrecto.\n";
	
	fin.close();
	return isValid;
}

/**
 * Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
 * por el parametro space.
 */
void Bmp::Hide(Space& space, Message& msg)
{
	fstream fin(space.GetFilePath()), fdata(msg.GetFilePath());
	UBYTE dataByte, imgByte;
	long hideBytes = 0;
	
	fin.seekp(space.GetInitialPosition());
	
	while(!fdata.eof() && (hideBytes < space.GetSize()))
	{
		fdata >> dataByte;
		
		for(int k=0;k<8;k++)
		{
			fin >> imgByte;
			imgByte = (imgByte & ~1) | ((dataByte>>(7-k))&1);
		}
	}
	
	
	
}
