#include "Image.h"

Image::Image(){

}

Image::Image(const char* filePath)
{
	this->filePath = filePath;
}

Image::~Image(){

}

Space* Image::Load()
{
	return false;
}

/**
 * Tamano total en bytes del archivo donde esta contenido el espacio.
 */
long Image::GetTotalSize() const
{
	long pos = 0;
	std::ifstream fin(this->filePath);
	if(fin)
	{
	   fin.seekg(0, std::ios::end); 
	   pos = fin.tellg();
	}
	fin.close();
	return pos;
}
