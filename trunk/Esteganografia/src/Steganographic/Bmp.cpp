///////////////////////////////////////////////////////////
//  Bmp.cpp
//  Implementation of the Class Bmp
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Bmp.h"

using namespace std;

Bmp::Bmp(const char* filePath)
{
	this->filePath = filePath;
}

Bmp::~Bmp()
{
}

Space* Bmp::Load()
{
	fstream file(filePath);
	BmpInfoHeader bmpInfoHeader;
	long spaceTotal = 0;
	Space *space = NULL;
	if( file.bad() )
	{
		cout << ERR_FILE_OPEN << this->filePath << endl;
		return NULL;
	}
	file.seekg(14);
	file.read((char*)&bmpInfoHeader,sizeof(bmpInfoHeader));
	file.seekg(0, ios::end);
	spaceTotal = file.tellg();
	spaceTotal-=STARTBYTE;
	switch( bmpInfoHeader.biBitCount)
	{
		case 1:
		{
			spaceTotal = 0;
			break;
		}
		case 4:
		case 8:
		{
			spaceTotal = spaceTotal/8;
			break;
		}
		case 16:
		case 24:
		case 32:
		{
			spaceTotal = spaceTotal / 4;
			break;
		}
		default:
		{
			spaceTotal = 0;
			break;
		}
	}
	if( spaceTotal > 0)
		space = new Space(filePath, BmpFileType, STARTBYTE, spaceTotal);
	file.close();
	return space;
}

/**
 * Implementar el comportamiento para extraer la informacion en un lugar
 * determinado.
 */
void Bmp::Extract(Space* space, Message* msg)
{
	long spaceSize = space->GetSize();
	fstream fin(space->GetFilePath(), ios::in | ios::binary);
	fstream fdata(msg->GetFilePath(),ios::out | ios::binary | ios::app);
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

	return 1;
}

ImageColor Bmp::ImageInfo(const char* filePath)
{
	BmpInfoHeader bmpInfoHeader;
	fstream fin(filePath);
	ImageColor color = LowColor;

	if(fin.bad())
	{
		cout << ERR_FILE_OPEN << filePath << "\n";
		return InvalidColor;
	}

	fin.seekg(14);
	fin.read((char*)&bmpInfoHeader,sizeof(bmpInfoHeader));

	cout << "Size of " << filePath << " = " << bmpInfoHeader.biSizeImage/1024 << "KB\n";
	cout << "Width of Bitmap File = " << bmpInfoHeader.biWidth << "\n";
	cout << "Height of Bitmap File = " << bmpInfoHeader.biHeight << "\n";
	switch(bmpInfoHeader.biBitCount)
	{
		case 1:
			cout << "Monochrome Image 1bit (2 color)\n";
			break;
		case 4:
			cout << "VGA Image ->4bit (16 color)\n";
			break;
		case 8:
			cout << "SVGA or greyscale ->8bit (256 color)\n";
			break;
		case 16:
			cout << "High Color ->16bit (65536 colour)\n";
			break;
		case 24:
		{
			cout << "True Color ->24bit (16.7 Mio colour)\n";
			color = HighColor;
			break;
		}
		default:
		{
			color = HighColor;
			cout << "Unknown color depth = " << bmpInfoHeader.biBitCount << "\n";
			break;
		}
	}

	if(bmpInfoHeader.biCompression != 0)
		cout << "BitMap File <"<< filePath << "> is Compressed\n";
	else
		cout << "BitMap File <"<< filePath << "> is UnCompressed\n";

	fin.close();
	return color;
}

bool Bmp::ValidateFormat(const char *filePath)
{
	fstream fin(filePath);
	string format;
	string header(BmpFileType);
	bool isValid = false;

	if(fin.good())
	{
		fin >> format;
		if(format.compare(0,2,header) == 0)
		{
			cout << "Formato BMP correcto.\n";
			isValid = true;
		}
		fin.close();
	}
	else
	{
		cerr << ERR_FILE_OPEN << filePath << "\n";
	}
	return isValid;
}

/**
 * Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
 * por el parametro space.
 */
void Bmp::Hide(Space* space, Message* msg)
{
	long spaceSize = space->GetSize();
	fstream fin(space->GetFilePath(), ios::binary | ios::in | ios::out );
	fstream fdata(msg->GetFilePath() , ios::binary | ios::in);
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
