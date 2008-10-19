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
void Bmp::Extract(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fin(space->GetFilePath()), fdata(msg->GetFilePath(),ios::out | ios::app);
	long extractBytes = 0;

	fin.seekg(space->GetInitialPosition());
	
	while(extractBytes < spaceSize)
	{
		extractBytes += this->LsbExtract(fin, fdata);
	}
	
	fin.close();
	fdata.close();
}

long Bmp::LsbExtract(fstream& fin, fstream& fdata)
{
	UBYTE imgByte, dataByte;
	
	//Se utiliza LSB de 1 bit.
	for(int k=0;k<8;k++)
	{
		fin.read(&imgByte,sizeof(UBYTE));
		dataByte = (dataByte & ~ (1<<(7-k))) | ((imgByte & 1)<<(7-k));
	}
	fdata.write(&dataByte,sizeof(UBYTE));	
	
	return 8;
}

bool Bmp::ValidateFormat(Space* space)
{
	fstream fin(space->GetFilePath());
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
		cerr << "Error al abrir el archivo BMP." << space->GetFilePath() <<"\n";
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
void Bmp::Hide(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fin(space->GetFilePath()), fdata(msg->GetFilePath());
	UBYTE dataByte;
	long hideBytes = 0;
	
	fdata.seekg(msg->GetHiddenSize());
	fin.seekg(space->GetInitialPosition());
	
	while(!fdata.eof() && (hideBytes < spaceSize))
	{
		fdata.read(&dataByte,sizeof(UBYTE));
		this->LsbHide(dataByte,fin);
		hideBytes++;
	}
	msg->IncHiddenSize(hideBytes);
	
	fin.close();
	fdata.close();
}

void Bmp::LsbHide(UBYTE dataByte,fstream& fin)
{
	long pos = 0;
	UBYTE imgByte;
	
	//Se utiliza LSB de 1 bit.
	for(int k=0;k<8;k++)
	{
		pos = fin.tellp();
		fin.read(&imgByte,sizeof(UBYTE));
		imgByte = (imgByte & ~1) | ((dataByte>>(7-k))&1);
		fin.seekp(pos);
		fin.write(&imgByte,sizeof(UBYTE));			
	}
}
