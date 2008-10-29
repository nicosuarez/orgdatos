///////////////////////////////////////////////////////////
//  Bmp.h
//  Implementation of the Class Bmp
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B2D82F06_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B2D82F06_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include <fstream>
#include <iostream>
#include "Image.h"

#define BUFSIZE 1024 //512
#define DATASIZE 64
#define STARTBYTE 64
#define BmpFileType "BM"

typedef enum ImageColor { InvalidColor= -1, HighColor=0, LowColor=1 } ImageColor;

/**
 * Estructuras del header del formato BMP
 */
typedef struct BmpFileHeader
{
	unsigned char bfType;   //Tipo de archivo (2 bytes) debe ser 'BM'.
	unsigned int bfSize;    //Tamano del archivo (4 bytes).
	short int bfReserved1;  //Reservado=0 (2 bytes).
	short int bfReserved2;  //Reservado=0 (2 bytes).
	unsigned int bfOffbits; //Inicio de los datos de la imagen en bytes (4 bytes).
	// Para los 8-bit bitmaps, el tamano va a ser sizeof(BitMapFileHeader) +
	//sizeof(BitMapInfoHeader) + sizeof(RGBQUAD) * numPaletteEntries.
}BmpFileHeader;


typedef struct BmpInfoHeader
{
	unsigned int biSize; 			//Tamano del header del bitmap sizeof(BmpInfoHeader) = sizeof(BitMapInfoHeader) (4 bytes).
	unsigned int biWidth; 			//Ancho del bitmap, en pixels. (4 bytes)
	unsigned int biHeight; 			//Alto del bitmap, en pixels. (4 bytes)
	short int biPlanes; 			//Numero de planos Set=1 (2 bytes).
	short int biBitCount; 			//El tamano de cada punto (bit depth). Para bitmaps de 8 bits este es 8. (2 bytes)
	unsigned int biCompression; 	//Nuestros bitmaps son no comprimidos, entonces el campo va en 0. (2 bytes)
	unsigned int biSizeImage; 		//Tamano de la imagen en bytes. (4 bytes)
	unsigned int biXPelsPerMeter;   //Resolocion Horizontal, en pixels por metro. No es significante se setea en 0. (4 bytes).
	unsigned int biYPelsPerMeter;   //Resolucion Vertical resolution, en pixels por metro. No es significante se setea en 0. (4 bytes).
	unsigned int biClrUsed; 		//Indica cuantos colores tiene la tabla. (4 bytes)
	unsigned int biClrImportant; 	//Indica cuantos colores son necesarios para mostrar el bitmap. Setea a 0 indicando que todos los colores deberian ser usados. (4 bytes)
}BmpInfoHeader;

/**
 * Formato BitMap soporta 16bits,24bits,256 colors.
 * Se utiliza LSB de 1bit o 2 bit para ocultar la informacion dependiendo la profundidad del color.
 */
class Bmp : public Image
{

public:
	Bmp(const char* filePath);
	Bmp();
	virtual ~Bmp();

	void Extract(Space* space, Message* msg);
	void Hide(Space* space, Message* msg);
	static bool ValidateFormat(Space* space);
	virtual void LsbHide(UBYTE dataByte,fstream& fin);
	virtual long LsbExtract(fstream& fin, fstream& fdata);
	static ImageColor ImageInfo(const char* filePath);

};
#endif // !defined(EA_B2D82F06_98EA_11dd_B49B_001B2425640C__INCLUDED_)
