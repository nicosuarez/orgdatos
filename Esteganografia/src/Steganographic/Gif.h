#if !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"
#include "../Common/Resource.h"
#include <list>
#include <math.h>

using std::fstream;
using std::ios;
using std::cout;
using std::endl;

#define BLOCK_TERMINATOR 0x00
#define EXTENSION_INTRODUCER 0x21
#define APP_EXTENSION_LABEL 0xff
#define GRAPHIC_CONTROL_LABEL 0xf9
#define COMMENT_LABEL 0xfe
#define PLAIN_TEXT_LABEL 0x01
#define IMAGE_SEPARATOR 0x2c
#define GIF_TRAILER 0x3b
#define OLD_SIGNATURE "GIF87a"
#define NEW_SIGNATURE "GIF89a"
#define GifFileType "GIF"

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

class Gif : public Image
{

public:
	Gif(const char *filePath);
	
	virtual ~Gif();
	
	/*Devuelve el espacio libre inicial*/
	Space* Load();
	
	/*Verifica si el archivo es del tipo GIF*/
	static bool ValidateFormat(const char* filePath);
	
	/* Implementa el comportamiento para extraer la informacion 
	 * en un lugar determinado.*/
	void Extract(Space* space, Message* msg);
	
	/* Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
	 * por el parametro space.*/
	void Hide(Space* space, Message* msg);
	
	/* Cantidad de informacion (bits) que se pueden ocultar por cada bytes 
	 * de la imagen */
	unsigned int GetBitsLsb() const{
		return BitsLsb;
	}
	
private:
	virtual long LsbExtract(fstream& fin, fstream& fdata);
	virtual void LsbHide(UBYTE dataByte,fstream& fin);

	static const unsigned int BitsLsb = 4;
	
};
#endif // !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
