///////////////////////////////////////////////////////////
//  Gif.h
//  Implementation of the Class Gif
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"
#include <list>
#include <math.h>

/**
 * Gif Formato.
 */
#define BLOCK_TERMINATOR 0x00
#define EXTENSION_INTRODUCER 0x21
#define APP_EXTENSION_LABEL 0xff
#define GRAPHIC_CONTROL_LABEL 0xf9
#define IMAGE_SEPARATOR 0x2c
#define GIF_TRAILER 0x3b

typedef struct GifFileHeader 
{
	char signature[3]; 
	char version[3];
};

typedef struct GifFileLogicalScreenDescriptor
{
	unsigned short  screenWidth, screenHeight;
	unsigned char packedFields, backgroundColor, pixelAspectRatio;
};

typedef struct GifFileAppExtension
{
	unsigned char blockSize;
	char appIdentifier[8];
	char appAuthCode[3];
};

typedef struct GifFileGraphicControlExtension
{
	unsigned char blockSize;
	unsigned char packedFields;
	unsigned short delayTime;
	unsigned char transparentColorIndex;
};

typedef struct GifFileImageDescriptor
{
	unsigned short imageLeftPosition;
	unsigned short imageTopPosition;
	unsigned short imageWidth;
	unsigned short imageHeight;
	unsigned char packedFields;
};


typedef struct GifInfoHeader
{
	char version[3]; //Version del GIF. Puede ser 87a u 89a.
	unsigned short width; //ancho de la imagen
	unsigned short height; //altura de la imagen
	unsigned int globalColorTable; //indica la presencia de la paleta global
	unsigned int colorResolution; //numero de bits por color primario
	unsigned sortFlag; //indica si la paleta esta ordenada. El orden es decreciente por frecuencia del color
	unsigned sizeGlobalColorTable; //Tamaño de la paleta;
	unsigned int backgroundColorIndex; //index de la paleta, del color del fondo de la imagen 
	unsigned int pixelAspectRatio; //
};

typedef struct GifImageDescriptor
{
	unsigned char imageSeparator;
	unsigned short imageLeftPosition;
	unsigned short imageTopPosition;
	unsigned short imageWidth;
	unsigned short imageHeight;
	unsigned int localColorTable;
	unsigned int interlaceFlag;
	unsigned int sortFlag;
	unsigned int reserved;
	unsigned int sizeLocalColorTable;
};



class Gif : public Image
{

public:
	Gif();
	Gif(char *filePath);
	virtual ~Gif();

	void Extract(Space* space, Message* msg);
	void Hide(Space* space, Message* msg);
	virtual long LsbExtract(fstream& fin, fstream& fdata);
	virtual void LsbHide(UBYTE dataByte,fstream& fin);
	list<Space*>* getSpaces(char *path);
	
};
#endif // !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
