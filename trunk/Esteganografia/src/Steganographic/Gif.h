///////////////////////////////////////////////////////////
//  Gif.h
//  Implementation of the Class Gif
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"
#include "../Common/Resource.h"
#include <list>
#include <math.h>

/**
 * Gif Formato.
 */
#define BLOCK_TERMINATOR 0x00
#define EXTENSION_INTRODUCER 0x21
#define APP_EXTENSION_LABEL 0xff
#define GRAPHIC_CONTROL_LABEL 0xf9
#define COMMENT_LABEL 0xfe
#define PLAIN_TEXT_LABEL 0x01
#define IMAGE_SEPARATOR 0x2c
#define GIF_TRAILER 0x3b

#define SIZE_HEADER 6
#define SIZE_SCREEN_DESCRIPTOR 7
#define SIZE_APP_EXTENSION 16
#define SIZE_GRAPHIC_EXTENSION 5
#define SIZE_PLAIN_TEXT_EXTENSION 13


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
	unsigned char appIdentifier[8];
	unsigned char appAuthCode[3];
	unsigned char appData[4];
};

typedef struct GifFileGraphicControlExtension
{
	unsigned char blockSize;
	unsigned char packedFields;
	unsigned short delayTime;
	unsigned char transparentColorIndex;
};

typedef struct GifPlainTextExtension
{
	unsigned char blockSize;
	unsigned short gridLeftPosition;
	unsigned short gridTopPosition;
	unsigned short gridWidth;
	unsigned short gridHeight;
	unsigned char charCellWidth;
	unsigned char charCellHeight;
	unsigned char textForegroundColorIndex;
	unsigned char textBackgroundColorIndex;
};

typedef struct GifFileImageDescriptor
{
	unsigned short imageLeftPosition;
	unsigned short imageTopPosition;
	unsigned short imageWidth;
	unsigned short imageHeight;
	unsigned char packedFields;
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
	Space* GetFreeSpace();
	
};
#endif // !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
