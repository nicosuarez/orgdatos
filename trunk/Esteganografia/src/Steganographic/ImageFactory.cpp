///////////////////////////////////////////////////////////
//  ImageFactory.cpp
//  Implementation of the Class ImageFactory
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "ImageFactory.h"

using namespace std; 

ImageFactory::ImageFactory(){

}

ImageFactory::~ImageFactory(){

}

/**
 * Retorna la imagen segun el formato del espacio.
 */
bool ImageFactory::SupportedFormats(const char* filePath)
{
	string path(filePath);
	string ext;
	string::size_type extPos = path.find_last_of(".");
	cout << "Path:" << filePath << "\n";
	if ( extPos != string::npos)
	{
		ext = path.substr(extPos,5);
		StrToken::toLowerString(ext);
		cout << ext << "\n";
		if(ext == EXT_BMP || ext == EXT_JPG || 
			ext == EXT_JPEG || ext == EXT_PNG || ext == EXT_GIF)
			return true;
	}
	return false;
}

/**
 * Retorna la imagen segun el formato del espacio.
 */
Image* ImageFactory::GetImage(const char* filePath)
{
	Space space(filePath);
	Image* image = NULL;
	if(Bmp::ValidateFormat(filePath))
	{
		ImageColor color = Bmp::ImageInfo(filePath); 
		if(color == LowColor)
		{
			image = new Bmp(filePath);
		}
		else if (color == HighColor)
		{
			image = new BmpHighColor(filePath);
		}
		else
		{
			cerr << "Error Bmp ImageInfo color\n";
		}
			
	}
	else if(Jpg::ValidateFormat(filePath))
	{
		image = new Jpg(filePath);
	}
	else if(Png::ValidateFormat(filePath))
	{
		image = new Png(filePath);
	}
	else if(Gif::ValidateFormat(filePath))
	{
		image = new Gif(filePath);
	}
	else
	{
		cout << ERR_IMAGE_NOT_SUPPORT << filePath << "\n";
	}
	
	return image;
}


/**
 * Retorna la imagen la cual corresponde a ese espacio.
 */
Image* ImageFactory::GetImage(Space* space)
{
	return GetImage(space->GetFilePath());
}
