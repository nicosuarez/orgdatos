///////////////////////////////////////////////////////////
//  Png.cpp
//  Implementation of the Class Png
//  Created on:      13-Oct-2008 2:49:35 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Png.h"


Png::Png(){

}

Png::Png(const char* filePath){
	this->filePath = filePath;
}

Png::~Png(){

}


/**
 * Implementar el comportamiento para extraer la informacion en un lugar
 * determinado.
 */
void Png::Extract(Space* space, Message* msg){
	
}


/**
 * Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
 * por el parametro space.
 */
void Png::Hide(Space* space, Message* msg)
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

void Png::LsbHide(UBYTE dataByte,fstream& fin)
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

bool Png::ValidateFormat(Space* space)
{
	fstream fin(space->GetFilePath());
	fin.seekg(1);
	string format;
	string header(PngFileType);
	bool isValid = false;
    
	if(fin.good())
	{
		fin >> format;
		if(format.compare(0,3,header) == 0)
		{
			cout << "Formato PNG Correcto.\n";
			isValid = true;
		}
	}
	else
	{
		cerr << "Error al abrir el archivo PNG." << space->GetFilePath() <<"\n";
	}
		
	fin.close();
	return isValid;
}


tListSpaces* Png::GetFreeSpaces(char * path)
{
	fstream file(path);
	if( file.bad())
	{
		cout << "NO SE PUDO ABRIR LA IMAGEN: " << path << endl; 
		return NULL;
	}
	tListSpaces* lista = new tListSpaces();
//	Space *space;
//	GifFileHeader header;
//	GifFileLogicalScreenDescriptor lsd;
//	int sizePaleta=0, pos=0;
	
	//leo el header de la imagen
//	file.read((char*)&header, sizeof(GifFileHeader));
	
	//leo el logical screen description, para ver si hay paleta global
//	file.read((char*)&lsd, sizeof(GifFileLogicalScreenDescriptor));
//	if( (lsd.packedFields >> 7) == 1 )//si hay paleta global
//	{
//		//obtengo el tamaño de la paleta
//		sizePaleta = lsd.packedFields & 0x07;
//		sizePaleta = 3*(int)pow(2,(double)sizePaleta+1);
//		
//		//obtengo posicion donde esta la paleta
//		pos = file.tellg();
//		
//		//doy de alta un nuevo espacio libre y lo agrego a la lista
//		space = new Space(path, "GIF", pos, sizePaleta);
//		lista->push_back(space);
//		
//		//posiciono el puntero al final de la paleta
//		file.seekg(sizePaleta, ios_base::cur);
//	}
//	
//	//sigo leyendo en busca de paletas locales
//	char buf;
//	file.read(&buf, sizeof(char));
//	
//	//si hay bloques extension los salteo porque no me interesan
//	if( buf  == EXTENSION_INTRODUCER)
//	{
//		file.read(&buf, sizeof(char));
//		if( (unsigned char)buf == APP_EXTENSION_LABEL)
//		{
//			file.seekg(sizeof(GifFileAppExtension), ios_base::cur);
//			file.read(&buf, sizeof(char));
//			while( buf != BLOCK_TERMINATOR)
//				file.read(&buf, sizeof(char));
//			file.read(&buf, sizeof(char));
//		}
//		if( (unsigned char)buf == GRAPHIC_CONTROL_LABEL)
//		{
//			file.seekg(sizeof(GifFileGraphicControlExtension) + 1, ios_base::cur);
//			file.read(&buf,sizeof(char));
//		}
//	}
//	
//	GifFileImageDescriptor imageDescriptor;
//	
//	//por cada imagen que hay en el gif me fijo en su "image descriptor" si tiene paleta local
//	while(buf == IMAGE_SEPARATOR)	
//	{
//		file.read((char*)&imageDescriptor, sizeof(GifFileImageDescriptor));
//		if( (imageDescriptor.packedFields >> 7) == 1) //si hay paleta local
//		{
//			sizePaleta = imageDescriptor.packedFields & 0x07;
//			sizePaleta = 3*(int)pow(2,(double)sizePaleta+1);
//			pos = file.tellg();
//			space = new Space(path, "GIF", pos, sizePaleta);
//			lista->push_back(space);
//			file.seekg(sizePaleta+1, ios_base::cur); //posiciono donde empieza el bloque de datos
//			file.read(&buf, sizeof(char)); //leo el tamaño del bloque
//			file.seekg( ((int)buf)+1, ios_base::cur);//posiciono al final del bloque de datos
//		}
//		file.read(&buf, sizeof(char));
//	}
//	file.close();
	return lista;
}
