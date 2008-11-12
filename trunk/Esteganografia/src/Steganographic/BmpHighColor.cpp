///////////////////////////////////////////////////////////
//  BmpHighColor.cpp
//  Implementation of the Class BmpHighColor
//  Created on:      17-Oct-2008 3:48:10 PM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "BmpHighColor.h"


BmpHighColor::BmpHighColor(const char* filePath):Bmp(filePath)
{
}

BmpHighColor::~BmpHighColor(){

}

/**
 * Extrae el mensaje oculto en la imagen en el lugar indicado tomando los ultimos 2
 * bit de cada byte en la imagen. Retornando la cantidad de bytes extraidos del
 * espacio.
 */
long BmpHighColor::LsbExtract(fstream& fin, fstream& fdata)
{
	UBYTE imgByte, dataByte;
		
	//Se utiliza LSB de 2 bits.
	for(int k=0;k<4;k++)
	{
		fin.read(&imgByte,sizeof(UBYTE));
		dataByte = (dataByte & ~ (3<<(6-(2*k)))) | ((imgByte & 3)<<(6-(2*k)));
	}
	fdata.write(&dataByte,sizeof(UBYTE));	
	
	return 4;
}


/**
 * Oculta el mensaje en el lugar indicado modificando los 2 ultimos bits de cada byte
 * en la imagen.
 */
void BmpHighColor::LsbHide(UBYTE dataByte,fstream& fin)
{
	long pos = 0;
	UBYTE imgByte;
	
	//Se utiliza LSB de 2 bits.
	for(int k=0;k<4;k++)
	{
		pos = fin.tellp();
		fin.read(&imgByte,sizeof(UBYTE));
		imgByte = (imgByte & ~3) | ((dataByte>>(6-2*k))&3);
		fin.seekp(pos);
		fin.write(&imgByte,sizeof(UBYTE));			
	}
}
