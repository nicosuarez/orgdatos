#include "Png.h"

Png::Png()
{	
}
/*---------------------------------------------------------------------------*/
Png::~Png()
{
}
/*---------------------------------------------------------------------------*/
Png::Png(const char* filePath) : Image(filePath)
{
}
/*---------------------------------------------------------------------------*/
Space* Png::GetFreeSpace()
{
	long initialPosition=0;
	SetPngInfo(this->GetFilePath());
	long totalComponents = (this->Height * this->Width) * this->Channels;
	long freeSpace = (totalComponents / (8/BitsLSB));
	
	Space* space = new Space(this->GetFilePath());
	space->SetInitialPosition(initialPosition);
	space->SetSize(freeSpace);
	return space;
}
/*---------------------------------------------------------------------------*/
bool Png::ValidateFormat(const char* filePath)
{
	png_byte header[8];
    FILE *fp = fopen(filePath, "rb");
    if (!fp)
    {
    	cerr << ERR_FILE_OPEN << filePath <<"\n";
        throw EMPTY;
    }
    fread(header, 1, 8, fp);
    bool is_png = !png_sig_cmp(header, 0, 8);
	fclose(fp);
	return is_png;
}
/*---------------------------------------------------------------------------*/
void Png::Hide(Space* space, Message* msg)
{
	//Verifica que tipo de profundidad de color tiene para realizar 
	//el ocultamiento (Tipos: RGB,RGBA,GA,GRAY 16 y 8 bits)
	try
	{
		this->SetPngInfo(space->GetFilePath());
		if(this->BitDepth == HighBitDepth)
			this->Hide<png_uint_16>(space,msg);
		else
			this->Hide<png_byte>(space,msg);
	}
	catch (char* error)
    {
		std::cout << error << std::endl;
    }
}
/*---------------------------------------------------------------------------*/
void Png::Extract(Space* space, Message* msg)
{
	//Verifica que tipo de profundidad de color tiene para realizar 
	//el ocultamiento (Tipos: RGB,RGBA,GA,GRAY 16 y 8 bits)
	try
	{
		SetPngInfo(space->GetFilePath());
		if(this->BitDepth == HighBitDepth)
			this->Extract<png_uint_16>(space,msg);
		else
			this->Extract<png_byte>(space,msg);
	}
	catch (char* error)
    {
		std::cout << error << std::endl;
    }
}
/*---------------------------------------------------------------------------*/
FILE* Png::OpenImage(const char* filePath, const char* mode)
{
	FILE* inputFile;
    if ((inputFile = fopen(filePath,mode))== NULL)
    {
    	cout << ERR_FILE_OPEN << filePath << endl;
    	throw EMPTY;
    }
    
    return inputFile;
}
/*---------------------------------------------------------------------------*/
void Png::SetPngInfo(const char* filePath)
{
	FILE* imageFile = OpenImage(filePath, "r+b");
	CreateReadPng(imageFile);
	CreateInfo();
	ValidateReadInfo(imageFile);
	ValidatePng(imageFile);
	ReadPng(imageFile);
	GetIHDR(Width, Height, BitDepth, ColorType, InterlaceType, 
			CompressionType ,FilterMethod );
	this->Channels = GetChannels();
	this->RowBytes = GetRowBytes();
	DeleteReadPng(imageFile);
}
/*---------------------------------------------------------------------------*/
bool Png::CreateReadPng(FILE* inputFile)
{
	PngStruct = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL ,
									       NULL ,
									       NULL );
	if (PngStruct== NULL)
	{
		fclose(inputFile);
		throw ERR_CREATE_PNG_STRUCT_WRITE;
	}
	return false;
}
/*---------------------------------------------------------------------------*/
void Png::CreateInfo()
{
	InfoStruct = png_create_info_struct( PngStruct );
}
/*---------------------------------------------------------------------------*/
bool Png::ValidatePng(FILE* inputFile)
{
	if (setjmp(png_jmpbuf(PngStruct)))
	{
		DeleteReadPng(inputFile);
	    throw ERR_VALIDATE_PNG_FORMAT;
	} 
	return false; //No error
}
/*---------------------------------------------------------------------------*/
void Png::ReadPng(FILE* inputFile)
{ 
	unsigned int sig_read=0;
	InitIO(inputFile); 
	png_set_sig_bytes( PngStruct , sig_read );
	png_read_png( PngStruct , InfoStruct , PNG_TRANSFORM_IDENTITY , NULL );
}
/*---------------------------------------------------------------------------*/
void Png::GetIHDR(png_uint_32& width, png_uint_32& height, int& bit_depth, 
					int& color_type, int& interlace_type ,
					int& compression_type, int& filter_method)
{  
	png_get_IHDR( 
	  PngStruct , 
	  InfoStruct , 
	  &width , 
	  &height ,
	  &bit_depth , 
	  &color_type , 
	  &interlace_type ,
	  &compression_type , 
	  &filter_method );
}
/*---------------------------------------------------------------------------*/
png_uint_32 Png::GetChannels()
{
	return png_get_channels(PngStruct, InfoStruct);
}
/*---------------------------------------------------------------------------*/
png_uint_32 Png::GetRowBytes()
{
	return png_get_rowbytes(PngStruct, InfoStruct);
}
/*---------------------------------------------------------------------------*/
void Png::InitIO(FILE* inputFile)
{
	png_init_io( PngStruct, inputFile);
}
/*---------------------------------------------------------------------------*/
bool Png::ValidateWriteInfo(FILE* outFile)
{
	if(InfoStruct==NULL)
	{
		DeleteWritePng(outFile);
		throw ERR_VALIDATE_INFO_PNG;
	}
	return false; //No error.
}
/*---------------------------------------------------------------------------*/
bool Png::ValidateReadInfo(FILE* outFile)
{
	if(InfoStruct==NULL)
	{
		DeleteReadPng(outFile);
		throw ERR_VALIDATE_INFO_PNG;
	}
	return false; //No error.
}
/*---------------------------------------------------------------------------*/
void Png::DeleteReadPng(FILE* inputFile)
{
	// Se destruye la estructura para lectura. 
	png_destroy_read_struct(&PngStruct , &InfoStruct , png_infopp_NULL);
	// se cierra el archivo.
	fclose( inputFile );
}
/*---------------------------------------------------------------------------*/
void Png::DeleteWritePng(FILE* onputFile)
{
	// Se destruye la estructura para escritura.  
	png_destroy_write_struct(&PngStruct , &InfoStruct);
	// se cierra el archivo.
	fclose( onputFile );
}
/*---------------------------------------------------------------------------*/
void Png::SetIHDR(png_uint_32 width, png_uint_32 height, int bit_depth, 
					int color_type, int interlace_type ,int compression_type,
					int filter_method)
{  
	png_set_IHDR( 
	  PngStruct , 
	  InfoStruct , 
	  width , 
	  height ,
	  bit_depth , 
	  color_type , 
	  interlace_type ,
	  compression_type , 
	  filter_method );
}
/*---------------------------------------------------------------------------*/
void Png::WriteInfo()
{ 
	png_write_info( PngStruct, InfoStruct);
}
/*---------------------------------------------------------------------------*/
void Png::WriteEnd()
{
	png_write_end(PngStruct , NULL);
}
/*---------------------------------------------------------------------------*/
bool Png::CreateWritePng(FILE* inputFile)
{
	PngStruct = 
	  png_create_write_struct( 
	    PNG_LIBPNG_VER_STRING ,
	    NULL , 
	    NULL , 
	    NULL );

	if (PngStruct == NULL) 
	{
		fclose(inputFile);
		throw ERR_CREATE_PNG_STRUCT_WRITE;
	}
		
	return false;
}
/*---------------------------------------------------------------------------*/
