///////////////////////////////////////////////////////////
//  ImageManager.cpp
//  Implementation of the Class ImageManager
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "ImageManager.h"
#include "../Tree/BppTree/treeIterator.h"
#include "../Tree/factory.h"
#include <string>

using namespace std;

unsigned long ImageManager:: totalFreeSize = 0;
ImageManager* ImageManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


ImageManager::ImageManager(): orgImages(PATH_MESSAGE_FILE, ImgRegistry::RegCreate),
							  orgListMsgs(PATH_MSG_LIST_FILE, ListMsgRegistry::Create),
							  orgNamesImages(PATH_NAMES_IMG_FILE),
							  orgNamesDir(PATH_NAMES_DIR_FILE),
							  imgTree(512,KeyStrFactory(), ValueIntFactory(),PATH_TREE_IMG)
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


void ImageManager::DeleteImage(Image* image){

}
/* -------------------------------------------------------------------------- */


ID_type ImageManager::AddImage(const char* imagePath){

	FreeSpaceManager* fsManager = FreeSpaceManager::GetInstance();
	Image* image = ImageFactory::GetImage(imagePath);
	if(image != NULL)
	{
		ImgRegistry imgReg;
		Space* space = image->Load();
		//Se crea el espacio libre.
		ID_type id = fsManager->AddFreeSpace(space);
		//Asignar los punteros al espacio libre.
		imgReg.setIDFirstFreeSpace(id);
		imgReg.setIDLastFreeSpace(id);
		//Asignar lista de mensajes
		imgReg.setPtrMsgList(NULL);
		//Asignar tamano de espacio libre.
		imgReg.setSizeMaxFreeSpace(space->GetSize());
		orgImages.WriteRegistry(imgReg);
		
		//Actualizo el arbol de imagenes.
		
	}
	
	return 1;
}
/* -------------------------------------------------------------------------- */
/*
 * Agrega todos los directorios y imagenes al arbol imgTree
 * Agrega agrega todas las imagenes al imgFile
 */
void ImageManager::AddDirectory(const char* dirPath)
{
	tVecStr fileList=FileSystem::GetFiles(dirPath,File);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
	ValueInt vDir(0);
	imgTree.insert(kDir,vDir);
	for(size_t i=0; i<fileList.size();i++){
		tVecStr tokensFile=StrToken::getStrTokens(fileList[i].c_str(),"/");
		if((tokensFile.size()-tokensDir.size())%2==0)
		{
			//es una imagen
			ID_type id = AddImage(fileList[i].c_str());
			KeyStr keyImg(fileList[i]);
			ValueInt valImg(id);
			this->imgTree.insert(keyImg,valImg);
		}
		else
		{
			//es un directorio
			KeyStr kSubDir(dirPath);
			ValueInt vSubDir(0);
			imgTree.insert(kSubDir,vSubDir);
		}
	}
}
/* -------------------------------------------------------------------------- */

void ImageManager::DeleteDirectory(const char* dirPath){
	tVecStr fileList=FileSystem::GetFiles(dirPath,File);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
	TreeIterator& it = imgTree.iterator(kDir);
	while (!it.end()){
		KeyStr* kStr=(KeyStr*)it.getKey();
		tVecStr tokens=StrToken::getStrTokens(kStr->getKey(),"/");
		if (!(tokens.size()>tokensDir.size()+1)){

		delete kStr;

		}
		++it;
	}

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
