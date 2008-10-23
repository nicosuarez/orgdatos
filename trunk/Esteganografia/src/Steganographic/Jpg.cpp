///////////////////////////////////////////////////////////
//  Jpg.cpp
//  Implementation of the Class Jpg
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Jpg.h"

using namespace std;

Jpg::Jpg(){

}

Jpg::~Jpg(){

}


/**
 * Implementar el comportamiento para extraer la informacion en un lugar
 * determinado.
 */
void Jpg::Extract(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fin(space->GetFilePath(), ios::binary), fdata(msg->GetFilePath(),ios::out | ios::app);
	long extractBytes = 0;
	UBYTE dataByte;

	fin.seekg(space->GetInitialPosition());
	
	while(extractBytes < spaceSize)
	{
		fin.read(&dataByte,sizeof(UBYTE));
		fdata.write(&dataByte,sizeof(UBYTE));
		extractBytes ++;
	}
	
	fin.close();
	fdata.close();
}


/**
 * Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
 * por el parametro space.
 */
void Jpg::Hide(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fin(space->GetFilePath(),ios::binary), fdata(msg->GetFilePath());
	UBYTE dataByte;
	long hideBytes = 0;
	
	fdata.seekg(msg->GetHiddenSize());
	fin.seekg(space->GetInitialPosition());
	
	while(!fdata.eof() && (hideBytes < spaceSize))
	{
		fdata.read(&dataByte,sizeof(UBYTE));
		fin.write(&dataByte,sizeof(UBYTE));
		hideBytes++;
	}
	msg->IncHiddenSize(hideBytes);
	
	fin.close();
	fdata.close();
}
