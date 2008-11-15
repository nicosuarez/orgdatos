///////////////////////////////////////////////////////////
//  ImageManager.cpp
//  Implementation of the Class ImageManager
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "ImageManager.h"

unsigned long ImageManager:: totalFreeSize = 0;
ImageManager* ImageManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


ImageManager::ImageManager(): orgImages(PATH_MESSAGE_FILE, ImgRegistry::RegCreate), 
							  orgListFreeSpaces(PATH_FREE_SPACE_FILE, ListFreeSpaceRegistry::Create),
							  orgListMsgs(PATH_MSG_LIST_FILE, ListMsgRegistry::Create),
							  orgNamesImages(PATH_NAMES_IMG_FILE),
							  orgNamesDir(PATH_NAMES_DIR_FILE)
{

}
/* -------------------------------------------------------------------------- */


ImageManager* ImageManager::GetInstance()
{
	if(instance == NULL)
		instance = new ImageManager();
	return instance;
}
/* -------------------------------------------------------------------------- */


ImageManager::~ImageManager()
{
	delete instance;
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


unsigned long ImageManager::GetTotalFreeSize() const
{
	return totalFreeSize;
}
/* -------------------------------------------------------------------------- */

list<Space> ImageManager::GetSpacesToStore(unsigned long sizeMsg)
{
	list<Space> lista;
	return lista;
}
