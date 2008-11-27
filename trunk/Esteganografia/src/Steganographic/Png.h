///////////////////////////////////////////////////////////
//  Png.h
//  Implementation of the Class Png
//  Created on:      13-Oct-2008 2:49:35 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#ifndef PNGRGB_H_
#define PNGRGB_H_

#include "Image.h"
#include <png.h>

#define PngFileType "PNG"

class Png : public Image
{
private:
	
	static const int HighBitDepth = 16;
	static const unsigned int BitsLSB = 2;
	
	// Informacion general del png
	png_uint_32  Width;
	png_uint_32  Height;
	png_uint_32  RowBytes;
	png_uint_32 Channels;
	int	BitDepth;
    int	ColorType;
    int	InterlaceType;
    int	CompressionType;
    int	FilterMethod;
	
    // Estructura principal del png
    png_structp  PngStruct;
    // Estructura con la informacion del png.
    png_infop InfoStruct;
    
    long posImageData;

    /**
	 * Metodos privados internos, validaciones y wrapper de la libpng 
	 */
    //Abre un file descriptor.
    FILE* OpenImage(const char* filePath, const char* mode);
    //Obtiene la cantidad de canales que tiene la imagen. Ej: si es RGB devuelve 3, RGBA 4.
    png_uint_32 GetChannels();
    //Obtiene la cantidad de bytes necesarios para almacenar una fila.
    png_uint_32 GetRowBytes();
    bool CreateReadPng(FILE* inputFile);
	bool CreateWritePng(FILE* inputFile);
	//Validaciones
	bool ValidateWriteInfo(FILE* outFile);
	bool ValidateReadInfo(FILE* inputFile);
	bool ValidatePng(FILE* inputFile);
	void InitIO(FILE* inputFile);
	void CreateInfo();
	void ReadPng(FILE* inputFile);
	void DeleteReadPng(FILE* inputFile);
	void DeleteWritePng(FILE* outFile);
	void WriteInfo();
	void WriteEnd();
	//Obtiene del fragmento IHDR toda la informacion basica de la imagen.
	void GetIHDR(png_uint_32& width, png_uint_32& height, int& bit_depth, 
				int& color_type, int& interlace_type ,int& compression_type,
				int& filter_method);
	//Sete en el fragmento IHDR toda la informacion basica de la imagen.
	void SetIHDR(png_uint_32 width, png_uint_32 height, int bit_depth, 
				int color_type, int interlace_type ,int compression_type, 
				int filter_method);
public:
	
	//Constructores y destructor
	Png();
	Png(const char* filePath);
	virtual ~Png();
	
	int	GetBitDepth(){
		return this->BitDepth;
	};
	
    int	GetColorType()
    {
    	return this->ColorType;
    };
    
    unsigned int GetBitsLsb() const{
		return BitsLSB;
	}
	
	/**
	 * Valida el formato png. 
	 */
	static bool ValidateFormat(const char* filePath);
	
	/**
	 * Metodo virtual que oculta un mensaje en el lugar especificado por 
	 * el espacio dependiendo de la profundidad de color de la imagen.
	 */	
	void Hide(Space* space, Message* msg);
	
	/**
	 * Obtiene la informacion basica del png. 
	 */
	void SetPngInfo(const char* filePath);
	
	/**
	 * Metodo virtual que extrae un mensaje en el lugar especificado por 
	 * el espacio dependiendo de la profundidad de color de la imagen.
	 */	
	void Extract(Space* space, Message* msg);
	
	/**
	 * Obtiene un bloque con el espacio disponible para almacenar informacion.
	 */
	Space* Load();

	/**
	 * Metodos templates, para poder utilizar forrmatos de png de 8 como de 
	 * 16 bits por componente de color 
	 */
	
	/**
	 * Metodo que oculta un mensaje en el lugar especificado por el espacio para
	 * para un tipo especifico, 8 o 16 bits.
	 */
	template<typename BitDepthType>
	void Hide(Space* space, Message* msg);
	
	/**
	 * Algoritmo de ocultamiento de informacion.
	 */
	template<typename BitDepthType>
	long LsbHide(UBYTE dataByte,BitDepthType** imageData,long position);
	
	/**
	 * Metodo que extrae un mensaje en el lugar especificado por el espacio para
	 * para un tipo especifico, 8 o 16 bits.
	 */
	template<typename BitDepthType>
	void Extract(Space* space, Message* msg);
	
	/**
	 * Metodo de ocultamiento de la informacion.
	 */
	template<typename BitDepthType>
	long LsbExtract(fstream& fdata, BitDepthType** imageData,long position);
	
	/**
	 * Metodo que graba una imagen png en el filePath con los datos de la
	 * imagen pasados por parametro.
	 */
	template<typename BitDepthType>
	void SaveImageData(const char* filePath, BitDepthType** imageData);
	
	/**
	 * Escribe los datos de la imagen en el PngStruct relacionado
	 */
	template<typename BitDepthType>
	void WriteImage(BitDepthType** imageData);
	
	/**
	 * Obtiene los datos de la imagen para que estos puedan ser modificados.
	 */
	template<typename BitDepthType>
	BitDepthType** GetImageData(const char* filePath);
	
	/**
	 * Copia los datos de la imagen en una nueva matriz.
	 */
	template<typename BitDepthType>
	BitDepthType** CreateImageData();

};

template<typename BitDepthType>
void Png::SaveImageData(const char* filePath, BitDepthType** imageData)
{
	FILE* outImage = OpenImage(filePath, "wb");
	CreateWritePng(outImage);
	CreateInfo();
	ValidateWriteInfo(outImage);
	ValidatePng(outImage);
	InitIO(outImage);
	ValidatePng(outImage);
	SetIHDR(Width, Height, BitDepth, ColorType , PNG_INTERLACE_NONE , 
			PNG_COMPRESSION_TYPE_BASE ,PNG_FILTER_TYPE_BASE );
	WriteInfo();
	ValidatePng(outImage);
	WriteImage(imageData);
	ValidatePng(outImage);
	WriteEnd();
	DeleteWritePng(outImage);
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
BitDepthType** Png::CreateImageData()
{
	png_uint_32 rowbytes = GetRowBytes();
	BitDepthType** imageData=(BitDepthType**)malloc(sizeof(BitDepthType*)*Height);
	
	if (!imageData)
		throw ERR_CREATE_IMAGE_PNG;

	// Se copia los datos de la imagen.
	for ( unsigned int y = 0; y < Height; ++y )
	{
		imageData[y] = (BitDepthType*)malloc(rowbytes);
		if (!imageData[y])
		   return false;
		memcpy(imageData[y], InfoStruct->row_pointers[y], rowbytes);
	}
	return imageData;
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
long Png::LsbExtract(fstream& fdata, BitDepthType** imageData, long position)
{
	UBYTE dataByte;
	BitDepthType imgByte;	
	
	//Se utiliza LSB de 2 bit.
	for(int k=0;k<4;k++)
	{
		long x=position% (Channels * Width);
		long y=position/ (Channels * Width);
		imgByte = imageData[y][x];
		dataByte = (dataByte & ~ (3<<(6-(2*k)))) | ((imgByte & 3)<<(6-(2*k)));
		position++;
	}
	fdata.write(&dataByte,sizeof(UBYTE));	
	
	return position;
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
void Png::Extract(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fdata(msg->GetFilePath(), ios::out | ios::binary | ios::app);
	long extractBytes = 0;
	BitDepthType** imageData = GetImageData<BitDepthType>(space->GetFilePath());
	long position = space->GetInitialPosition();
	
	while(extractBytes < spaceSize)
	{
		//Se extrae un byte por vez.
		position = this->LsbExtract<BitDepthType>(fdata, imageData, position);
		extractBytes++;
	}
	fdata.close();
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
BitDepthType** Png::GetImageData(const char* filePath)
{
	FILE* imageFile = OpenImage(filePath, "r+b");
	CreateReadPng(imageFile);
	CreateInfo();
	ValidateReadInfo(imageFile);
	ValidatePng(imageFile);
	ReadPng(imageFile);
	GetIHDR(Width, Height, BitDepth, ColorType, InterlaceType, 
			CompressionType ,FilterMethod );
	BitDepthType** imageData = CreateImageData<BitDepthType>();
	DeleteReadPng(imageFile);
	return imageData;
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
void Png::WriteImage(BitDepthType** imageData)
{
	png_write_image( PngStruct , (png_bytepp) imageData );
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
long Png::LsbHide(UBYTE dataByte, BitDepthType** imageData,long position)
{
	BitDepthType imgByte;

	//Se utiliza LSB de 2 bit.
	for(int k=0;k<4;k++)
	{
		long x=position% (Channels * Width);
		long y=position/ (Channels * Width);
		imgByte = imageData[y][x];
		imgByte = (imgByte & ~3) | ((dataByte>>(6-2*k))&3);
		imageData[y][x] = imgByte; 
		position++;
	}
	return position;
}
/*---------------------------------------------------------------------------*/
template<typename BitDepthType>
void  Png::Hide(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fdata(msg->GetFilePath(), ios::binary | ios::in);
	UBYTE dataByte;
	long hideBytes = -1;
	
	fdata.seekg(msg->GetHiddenSize());
	
	BitDepthType** imageData = GetImageData<BitDepthType>(space->GetFilePath());
	long position = space->GetInitialPosition();
	
	while(!fdata.eof() && (hideBytes < spaceSize))
	{
		fdata.read(&dataByte,sizeof(UBYTE));
		position = LsbHide<BitDepthType>(dataByte, imageData, position);
		hideBytes++;
	}
	SaveImageData<BitDepthType>(space->GetFilePath(), imageData);
	msg->IncHiddenSize(hideBytes);
	
	fdata.close();
}
/*---------------------------------------------------------------------------*/

#endif /*PNGRGB_H_*/
