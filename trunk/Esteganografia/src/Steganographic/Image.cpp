///////////////////////////////////////////////////////////
//  Image.cpp
//  Implementation of the Class Image
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Image.h"

using namespace std;

Image::Image(){

}

Image::Image(const char* filePath)
{
	this->filePath = filePath;
}

Image::~Image(){

}

bool Image::Load()
{
	return false;
}

/**
 * Tamano total en bytes del archivo donde esta contenido el espacio.
 */
long Image::GetTotalSize() const
{
	long pos = 0;
	ifstream fin(this->filePath);
	if(fin)
	{
	   fin.seekg(0, ios::end); 
	   pos = fin.tellg();
	}
	fin.close();
	return pos;
}
