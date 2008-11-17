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
							 // orgListFreeSpaces(PATH_FREE_SPACE_FILE, ListFreeSpaceRegistry::Create),
							  orgListMsgs(PATH_MSG_LIST_FILE, ListMsgRegistry::Create),
							 // orgNamesImages(PATH_NAMES_IMG_FILE),
							  //orgNamesDir(PATH_NAMES_DIR_FILE),
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


ID_type ImageManager::AddImage(Image* image){

	return 1;
}
/* -------------------------------------------------------------------------- */
/*
 * Agrega todos los directorios y imagenes al arbol imgTree
 * Agrega agrega todas las imagenes al imgFile
 */
void ImageManager::AddDirectory(const char* dirPath){
	tVecStr fileList=FileSystem::GetFiles(dirPath,File);
	//tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
	ValueInt vDir(0);
	imgTree.insert(kDir,vDir);
	for(size_t i=0; i<fileList.size();i++){
		tVecStr tokensFile=StrToken::getStrTokens(fileList[i].c_str(),"/");
		string strFile=string(dirPath)+ fileList[i];
		Image img(strFile.c_str());
		ID_type id=AddImage(&img);
		KeyStr keyImg(strFile.c_str());
		ValueInt valImg(id);
		this->imgTree.insert(keyImg,valImg);
	}
	tVecStr dirList=FileSystem::GetFiles(dirPath,Dir);
	for(size_t j=0; j<dirList.size();j++){
		string strdir=string(dirPath)+dirList[j];
		KeyStr kSubDir(dirPath);
		ValueInt vSubDir(0);
		imgTree.insert(kSubDir,vSubDir);
	}
}
/* -------------------------------------------------------------------------- */

void ImageManager::DeleteDirectory(const char* dirPath){
	bool end=false;
	tVecStr fileList=FileSystem::GetFiles(dirPath,File);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
	TreeIterator& it = imgTree.iterator(kDir);
	while ((!it.end())&&(end==false)){
		KeyStr* kStr=(KeyStr*)it.getKey();
		tVecStr tokens=StrToken::getStrTokens(kStr->getKey(),"/");
		if (((tokens.size()-tokensDir.size())%2==0)&&(tokens.size()-tokensDir.size()>0)){
			ValueInt* vInt=(ValueInt*)it.getValue();
			DeleteImage(vInt->getValue());
			imgTree.remove(*kStr);
			delete vInt;
		}else if (tokens.size()-tokensDir.size()>0)
			imgTree.remove(*kStr);
		else
			end=true;

		delete kStr;
		++it;
	}
}

/*void ImageManager::TestDirectory(const char* dirPath){
	tVecStr fileList=FileSystem::GetFiles(dirPath,File);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
}*/

/* -------------------------------------------------------------------------- */
void ImageManager::DeleteImage(ID_type id){

}

/* -------------------------------------------------------------------------- */
ID_type ImageManager::getId(const char* path){
	ID_type ans;
	KeyStr key(path);
	TreeIterator& it = imgTree.iterator(key);
	if(!it.end()){
		ValueInt* vInt=(ValueInt*)it.getValue();
		ans=vInt->getValue();
		delete vInt;
	}else
		ans=0;
	return ans;
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
