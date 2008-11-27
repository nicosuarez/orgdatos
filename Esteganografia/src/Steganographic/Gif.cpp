///////////////////////////////////////////////////////////
//  Gif.cpp
//  Implementation of the Class Gif
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: Nicolas
///////////////////////////////////////////////////////////

#include "Gif.h"


Gif::Gif(const char *filePath)
{
	this->filePath = filePath;
}
/* -------------------------------------------------------------------------- */

Gif::~Gif()
{
}
/* -------------------------------------------------------------------------- */

bool Gif::ValidateFormat(const char* filePath)
{
	fstream fin(filePath);
	string format;
	bool isValid = false;

	if(fin.good())
	{
		fin >> format;
		if( (format.compare(0,6,OLD_SIGNATURE) == 0) || (format.compare(0,6,NEW_SIGNATURE) == 0))
		{
			isValid = true;
		}
		fin.close();
	}
	else
	{
		cerr << ERR_FILE_OPEN << filePath<<"\n";
	}
	return isValid;
}
/* -------------------------------------------------------------------------- */

Space* Gif::Load()
{
	fstream file(this->filePath);
	if( file.bad())
	{
		cout << ERR_FILE_OPEN << this->filePath << endl;
		return NULL;
	}
	GifFileHeader header;
	GifFileLogicalScreenDescriptor lsd;
	unsigned short sizePaleta=0;
	Space *space = NULL;
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
		int initialPosition = file.tellg();

		//seteo el espacio libre disponible para almacenar informacion (4 bits de datos x byte de imagen)
		this->spaceTotal = sizePaleta/2;
		this->freeSpaceTotal = this->spaceTotal;
		space = new Space(this->filePath, GifFileType, initialPosition, spaceTotal);
	}
	file.close();
	return space;
}
/* -------------------------------------------------------------------------- */

void Gif::Extract(Space* space, Message* msg)
{
	long spaceSize = space->GetSize();
	fstream fin(space->GetFilePath(),  ios::in | ios::binary);
	fstream fdata(msg->GetFilePath(), ios::out | ios::binary | ios::app);
	long extractBytes = 0;

	fin.seekg(space->GetInitialPosition());

	while(extractBytes < spaceSize)
	{
		extractBytes += this->LsbExtract(fin, fdata);
	}
	fin.close();
	fdata.close();
}
/* -------------------------------------------------------------------------- */


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
/* -------------------------------------------------------------------------- */

void Gif::Hide(Space* space, Message* msg)
{
	long spaceSize = space->GetSize();
	fstream fin(space->GetFilePath(), ios::binary | ios::in | ios::out);
	fstream fdata(msg->GetFilePath(),  ios::binary | ios::in);
	UBYTE dataByte;
	long hideBytes = -1;

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
/* -------------------------------------------------------------------------- */

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
/* -------------------------------------------------------------------------- */

