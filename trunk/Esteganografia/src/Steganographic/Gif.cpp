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
		
	//Se utiliza LSB de 4 bits.
	for(int k=0;k<2;k++)
	{
		fin.read(&imgByte,sizeof(UBYTE));
		dataByte = (dataByte & ~ (15 << (4*(1-k)))) | ((imgByte & 15) << (4*(1-k)));
	}
	fdata.write(&dataByte,sizeof(UBYTE));
	
	return 1;
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
	
	//Se utiliza LSB de 4 bits.
	for(int k=0;k<2;k++)
	{
		pos = fin.tellp();
		fin.read(&imgByte, sizeof(UBYTE));
		imgByte = (imgByte & ~15) | ( (dataByte >> (4 *(1-k))) & 15 );
		fin.seekp(pos);
		fin.write(&imgByte, sizeof(UBYTE));
	}
}

Space* Gif::GetFreeSpace()
{
	fstream file(this->filePath);
	if( file.bad())
	{
		cout << ERR_FILE_OPEN << this->filePath << endl; 
		return NULL;
	}
	Space *space;
	GifFileHeader header;
	GifFileLogicalScreenDescriptor lsd;
	unsigned short sizePaleta=0, pos=0;//, sizeBloque=0;
	
	//leo el header de la imagen
	file.read((char*)&header, SIZE_HEADER);
	
	//leo el logical screen description, para ver si hay paleta global
	file.read((char*)&lsd, SIZE_SCREEN_DESCRIPTOR);
	if( (lsd.packedFields >> 7) == 1 )//si hay paleta global
	{
		//obtengo el tamaño de la paleta
		sizePaleta = lsd.packedFields & 0x07;
		sizePaleta = 3*(int)pow(2,sizePaleta+1);
		
		//obtengo posicion donde esta la paleta
		pos = file.tellg();
		
		//doy de alta un nuevo espacio libre y lo agrego a la lista
		space = new Space(this->filePath, "GIF", pos, sizePaleta/2);
		
//		lista->push_back(space);
		
		//posiciono el puntero al final de la paleta
		file.seekg(sizePaleta, ios_base::cur);
	}
	else return NULL;
	
//	//sigo leyendo en busca de paletas locales
//	unsigned char buf;
//	file.read((char*)&buf, sizeof(char));
//	//si hay bloques extension los salteo porque no me interesan
//	while( (buf  & EXTENSION_INTRODUCER) == EXTENSION_INTRODUCER )
//	{
//		file.read((char*)&buf, sizeof(char));
//		if( (buf & APP_EXTENSION_LABEL) == APP_EXTENSION_LABEL)
//		{
//			file.seekg(SIZE_APP_EXTENSION + 1, ios_base::cur);
//			cout << "HAY APP EXTENSION\n" ;
//			cout << "Pos: " << file.tellg() << endl;
//			file.read((char*)&buf, sizeof(char));
//			continue;
//		}
//		if( (buf & GRAPHIC_CONTROL_LABEL) == GRAPHIC_CONTROL_LABEL )
//		{
//			cout << "HAY GRAPHIC CONTROL EXTENSION\n";
//			file.seekg(SIZE_GRAPHIC_EXTENSION + 2, ios_base::cur);
//			cout << "Pos: " << file.tellg() << endl;
//			file.read((char*)&buf,sizeof(char));
//			continue;
//		}
//		if( (buf & PLAIN_TEXT_LABEL) == PLAIN_TEXT_LABEL)
//		{
//			cout << "HAY PLAIN TEXT EXTENSION\n";
//			file.seekg(SIZE_PLAIN_TEXT_EXTENSION, ios_base::cur);
//			cout << "Pos: " << file.tellg() << endl;
//			file.read((char*)&buf, sizeof(char));
//			do
//			{
//				sizeBloque = (unsigned char	)buf;
//				file.seekg( sizeBloque, ios_base::cur);
//				file.read((char*)&buf, sizeof(char));
//				cout << "Pos: " << file.tellg() << endl;
//				cout << "BLOQUE PLAIN TEXT NUEVO: " << sizeBloque << endl;
//				sizeBloque=0;
//			}while( buf != BLOCK_TERMINATOR );
//			continue;
//		}
//	}
//	
//	GifFileImageDescriptor imageDescriptor;
//	
//	//por cada imagen que hay en el gif me fijo en su "image descriptor" si tiene paleta local
//	while( (buf & IMAGE_SEPARATOR) != IMAGE_SEPARATOR )
//	{
//		file.read((char*)&imageDescriptor, 9);
//		if( (imageDescriptor.packedFields >> 7) == 1) //si hay paleta local
//		{
//			//obtengo el tamaño de la paleta
//			sizePaleta = imageDescriptor.packedFields & 0x07;
//			sizePaleta = 3*(int)pow(2,sizePaleta+1);
//			
//			//busco la posicion de la paleta dentro del archivo
//			pos = file.tellg();
//			
//			//doy de alta un nuevo espacio libre
//			space = new Space(filePath, "GIF", pos, sizePaleta);
//			lista->push_back(space);
//			
//			//posiciono donde empieza el bloque de datos
//			file.seekg(sizePaleta+1, ios_base::cur);
//			cout << "Paleta Local. Tamaño: " << sizePaleta << endl;
//		}
//		file.read((char*)&buf, sizeof(char));
//		sizeBloque=0;
//		do
//		{
//			sizeBloque = buf;
//			file.seekg( sizeBloque, ios_base::cur);
//			file.read((char*)&buf, sizeof(char));
//			cout << "BLOQUE NUEVO: " << sizeBloque << endl;
//			sizeBloque=0;
//		}while( (buf & ~BLOCK_TERMINATOR) != buf );
//		
//		file.read((char*)&buf, sizeof(char));
//	}
	file.close();
//	return lista;
	return space;
}


