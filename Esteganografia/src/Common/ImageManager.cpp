///////////////////////////////////////////////////////////
//  ImageManager.cpp
//  Implementation of the Class ImageManager
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "ImageManager.h"

unsigned long ImageManager:: freeTotalSize = 0;
ImageManager* ImageManager:: instace = NULL;
/* -------------------------------------------------------------------------- */


ImageManager::ImageManager(){

}
/* -------------------------------------------------------------------------- */


ImageManager* ImageManager::GetInstance()
{
	if(instace == NULL)
		instace = new ImageManager();
	return instace;
}
/* -------------------------------------------------------------------------- */


ImageManager::~ImageManager(){

}
/* -------------------------------------------------------------------------- */


void ImageManager::DeleteImage(Image* image)
{

}
/* -------------------------------------------------------------------------- */


void ImageManager::AddImage(Image* image)
{
}
/* -------------------------------------------------------------------------- */


list<int> ImageManager::GetMessages(Image* image)
{
	list<int> listMessages;
	return listMessages;
}
/* -------------------------------------------------------------------------- */


list<Space> ImageManager::GetFreeSpaces(Image* image)
{
	list<Space> listSpaces;
	return listSpaces;
}
/* -------------------------------------------------------------------------- */
