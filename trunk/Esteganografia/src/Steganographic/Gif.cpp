///////////////////////////////////////////////////////////
//  Gif.cpp
//  Implementation of the Class Gif
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Gif.h"


Gif::Gif()
{
	
}

Gif::Gif(char *filePath)
{
	this->filePath = filePath;
}



Gif::~Gif(){

}





/**
 * Implementar el comportamiento para extraer la informacion en un lugar
 * determinado.
 */
void Gif::Extract(Space* space, Message* msg)
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

long Gif::LsbExtract(fstream& fin, fstream& fdata)
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


/**
 * Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
 * por el parametro space.
 */

void Gif::Hide(Space* space, Message* msg)
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

void Gif::LsbHide(UBYTE dataByte,fstream& fin)
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

list<Space*>* Gif::getSpaces(char *path)
{
	fstream file(path);
	if( file.bad())
	{
		cout << "NO SE PUDO ABRIR LA IMAGEN: " << path << endl; 
		return NULL;
	}
	list<Space*> *lista = new list<Space*>;
	Space *space;
	GifFileHeader header;
	GifFileLogicalScreenDescriptor lsd;
	int sizePaleta=0, pos=0;
	
	//leo el header de la imagen
	file.read((char*)&header, sizeof(GifFileHeader));
	
	//leo el logical screen description, para ver si hay paleta global
	file.read((char*)&lsd, sizeof(GifFileLogicalScreenDescriptor));
	if( (lsd.packedFields >> 7) == 1 )//si hay paleta global
	{
		//obtengo el tamaño de la paleta
		sizePaleta = lsd.packedFields & 0x07;
		sizePaleta = 3*(int)pow(2,(double)sizePaleta+1);
		
		//obtengo posicion donde esta la paleta
		pos = file.tellg();
		
		//doy de alta un nuevo espacio libre y lo agrego a la lista
		space = new Space(path, "GIF", pos, sizePaleta);
		lista->push_back(space);
		
		//posiciono el puntero al final de la paleta
		file.seekg(sizePaleta, ios_base::cur);
	}
	
	//sigo leyendo en busca de paletas locales
	char buf;
	file.read(&buf, sizeof(char));
	
	//si hay bloques extension los salteo porque no me interesan
	if( buf  == EXTENSION_INTRODUCER)
	{
		file.read(&buf, sizeof(char));
		if( (unsigned char)buf == APP_EXTENSION_LABEL)
		{
			file.seekg(sizeof(GifFileAppExtension), ios_base::cur);
			file.read(&buf, sizeof(char));
			while( buf != BLOCK_TERMINATOR)
				file.read(&buf, sizeof(char));
			file.read(&buf, sizeof(char));
		}
		if( (unsigned char)buf == GRAPHIC_CONTROL_LABEL)
		{
			file.seekg(sizeof(GifFileGraphicControlExtension) + 1, ios_base::cur);
			file.read(&buf,sizeof(char));
		}
	}
	
	GifFileImageDescriptor imageDescriptor;
	
	//por cada imagen que hay en el gif me fijo en su "image descriptor" si tiene paleta local
	while(buf == IMAGE_SEPARATOR)	
	{
		file.read((char*)&imageDescriptor, sizeof(GifFileImageDescriptor));
		if( (imageDescriptor.packedFields >> 7) == 1) //si hay paleta local
		{
			sizePaleta = imageDescriptor.packedFields & 0x07;
			sizePaleta = 3*(int)pow(2,(double)sizePaleta+1);
			pos = file.tellg();
			space = new Space(path, "GIF", pos, sizePaleta);
			lista->push_back(space);
			file.seekg(sizePaleta+1, ios_base::cur); //posiciono donde empieza el bloque de datos
			file.read(&buf, sizeof(char)); //leo el tamaño del bloque
			file.seekg( ((int)buf)+1, ios_base::cur);//posiciono al final del bloque de datos
		}
		file.read(&buf, sizeof(char));
	}
	file.close();
	return lista;
}


