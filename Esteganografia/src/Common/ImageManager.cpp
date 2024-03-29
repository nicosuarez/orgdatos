///////////////////////////////////////////////////////////
//  ImageManager.cpp
//  Implementation of the Class ImageManager
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "ImageManager.h"
#include "../Tree/BppTree/treeIterator.h"
#include "../Tree/factory.h"
#include "./Exception/eNotExist.h"
#include <string>

unsigned long ImageManager:: totalFreeSize = 0;
ImageManager* ImageManager:: instance = NULL;

/* -------------------------------------------------------------------------- */


ImageManager::ImageManager(): orgImages(PATH_IMG_FILE, ImgRegistry::Create),
							  orgListMsgs(PATH_MSG_LIST_FILE, ListMsgRegistry::Create),
							  orgNamesImages(PATH_NAMES_IMG_PATHFILE, PATH_NAMES_IMG_FILE),
							  imgTree(512,KeyStrFactory(), ValueIntFactory(),PATH_TREE_IMG),
							  dirTree(512,KeyStrFactory(), ValueNullFactory(),PATH_TREE_DIR)
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

}
/* -------------------------------------------------------------------------- */
void ImageManager::ShowMessageFromDirectory(const char* dirPath)
{
    if( imgTree.empty())
        return;
    tVecStr fileList = FileSystem::GetFiles(dirPath,File);
    if(fileList.empty())
        return;
    std::list<string> listNameMsg;
    
    string strDirPath(dirPath);
    StrToken::FormatPath(strDirPath);
    
    for( unsigned int i=0; i<fileList.size(); i++)
    {
    	string fullPath = strDirPath + fileList[i];
        KeyStr key(fileList[i]);
        ValueInt* vInt = dynamic_cast<ValueInt*>(imgTree.find(key));
        if( vInt == NULL)
           continue;
        ImgRegistry* imgReg = dynamic_cast<ImgRegistry*>(orgImages.GetRegistry(vInt->getValue()));
        tRegisterList* listIdMsg = this->orgListMsgs.GetList(imgReg->GetPtrFreeSpaceList());
        if( listIdMsg != NULL )
        {
            itRegisterList it;
            MessageManager* messageManager = MessageManager::GetInstance();
            for( it=listIdMsg->begin(); it != listIdMsg->end(); it++ )
            {
                ListMsgRegistry* listMsgReg = dynamic_cast<ListMsgRegistry*>(*it);
                ID_type idMsg = listMsgReg->GetIDMessage();
                std::string nameMsg = messageManager->GetNameMessage(idMsg);
                listNameMsg.push_back(nameMsg);
                delete listMsgReg;
            }
            delete listIdMsg;
        }
       
        delete vInt;
        delete imgReg;
        delete listIdMsg;
    }
    listNameMsg.unique();
    std::list<string>::iterator it;
    for(it=listNameMsg.begin(); it != listNameMsg.end(); it++)
    {
        std::cout << (*it) << "\n";
    }
}
/* -------------------------------------------------------------------------- */
pListUpdate ImageManager::UpdateImages()
{
	pListUpdate updatesList;
	tVecStr* imgErasedList = GetUpdatedList(Erased);
	for(size_t i=0; i < imgErasedList->size(); i++)
	{
		string path = (*imgErasedList)[i];
		DeleteImage(path,imgErasedList);
	}
	
	tVecStr* imgAddList = GetUpdatedList(Added);
	for(size_t i=0; i < imgAddList->size(); i++)
	{
		string path = (*imgAddList)[i];
		AddImage(path.c_str());
	}
	updatesList.first = imgErasedList;
	updatesList.second = imgAddList;
	return updatesList;
}
/* -------------------------------------------------------------------------- */
void ImageManager::DeleteImage(string imgPath, tVecStr* imgErasedList, bool filterAll, bool removetoTree)
{
	KeyStr key(imgPath);
	if(!imgTree.empty())
	{
		if(imgTree.exists(key))
		{
			ValueInt* vInt = dynamic_cast<ValueInt*>(imgTree.find(key));
			DeleteImage(vInt->getValue(), imgErasedList, filterAll, removetoTree);
			delete vInt;
		}
	}
}
/* -------------------------------------------------------------------------- */


ID_type ImageManager::AddImage(const char* imagePath){
	KeyStr keyImg(imagePath);
	FreeSpaceManager* fsManager = FreeSpaceManager::GetInstance();
	ID_type idImg;
	if(!this->imgTree.exists(keyImg))
	{
		
		Image* image = ImageFactory::GetImage(imagePath);
		ImgRegistry imgReg;
		if(image != NULL)
		{
			Space* space = image->Load();
			if( space == NULL )
			{
				std::cout << ERR_IMAGE_WITHOUT_CAPACITY << ": " << imagePath << std::endl;
				return 0;
			}
					//Guardo el path completo de la imagen.
			ID_type idPath = orgNamesImages.WriteText(space->GetFilePath());
	
			//Asignar lista de mensajes
			imgReg.SetPtrMsgList(NULL);
			imgReg.SetPtrFreeSpaceList(NULL);
			imgReg.SetIDImagePath(idPath);
			Date date = Date::getDate(space->GetFilePath());
			imgReg.SetDate(date);
	
			//Guardar Imagen
			orgImages.WriteRegistry(imgReg);
	
			//Se crea el espacio libre.
			space->SetIDImage(imgReg.GetID());
			fsManager->AddFreeSpace(space);
		}
		idImg=imgReg.GetID();
		if (idImg!=0){
			ValueInt valImg(idImg);
			this->imgTree.insert(keyImg,valImg);
		}
	}else{
		return 1;
	}
	return idImg ;
}
/* -------------------------------------------------------------------------- */
void ImageManager::DeleteImage(ID_type idImg, tVecStr* imgErasedList, bool filterAll, bool removetoTree){

	ImgRegistry* img=dynamic_cast<ImgRegistry*>(orgImages.GetRegistry(idImg));
	FreeSpaceManager* fsManager = FreeSpaceManager::GetInstance();
	MessageManager* msgManager = MessageManager::GetInstance();
	
	//Obtener la lista de mensajes.
	if( img->GetPtrMsgList() > 0 )
	{
		tRegisterList* msgList = this->orgListMsgs.GetList(img->GetPtrMsgList());
		itRegisterList it = msgList->begin();

		//Eliminar mensajes asociados.
		while(it != msgList->end())
		{
			ListMsgRegistry* msgReg = dynamic_cast<ListMsgRegistry*>(*it);
			if(filterAll)
				msgManager->DeleteMessage(msgReg->GetIDMessage(),false, imgErasedList);
			else
				msgManager->DeleteMessage(msgReg->GetIDMessage(),true, imgErasedList);
			it++;
		}
	}
	
	//Eliminar Path
	string path=orgNamesImages.GetText(img->GetIDImagePath());
	orgNamesImages.DeleteText(img->GetIDImagePath());
	
	//Eliminar el espacio libre disponible.
	delete img;
	img = dynamic_cast<ImgRegistry*>(orgImages.GetRegistry(idImg));
	fsManager->RemoveFreeSpaceList(img->GetPtrFreeSpaceList());

	//Eliminar Registro Imagen.
	this->orgImages.DeleteRegistry(idImg);
	//Eliminar el arbol.
	KeyStr kImgTree(path.c_str());
	if (!imgTree.empty() && removetoTree)
		if (imgTree.exists(kImgTree))
			imgTree.remove(kImgTree);
}

/* -------------------------------------------------------------------------- */
/*
 * Agrega todos los directorios y imagenes al arbol imgTree
 * Agrega agrega todas las imagenes al imgFile
 */
tVecStr ImageManager::AddDirectory(const char* dirPath)
{
	tVecStr ans;
	tVecStr fileList=FileSystem::GetFiles(dirPath,All);
	
	if(fileList.size()==0)
		throw eNotExist(EMPTY);

	string strdir(dirPath);
	StrToken::FormatPath(strdir);
	string dirPathStr = strdir;

	KeyStr kDirDir(strdir);

	//Si el directorio existe no lo agrego.
	if (!dirTree.empty())
		if (dirTree.exists(kDirDir))
			throw eNotExist(WRONG_MSG_ADD_DIRECTORY);


	ans.push_back(strdir);
	strdir=strdir+END_DIRECTORY;
	KeyStr kDir(strdir);
	ValueInt vDir(0);
	ValueNull vNull;
	dirTree.insert(kDirDir,vNull);
	imgTree.insert(kDir,vDir);
	std::cout << std::endl;

	for(size_t i=0; i<fileList.size();i++)
	{
		string fullPath= dirPathStr + fileList[i];
		std::cout << ADDING_FILE << fullPath << std::endl;
		AddImage(fullPath.c_str());
	}

	tVecStr dirList=FileSystem::GetFiles(dirPath,Dir);

	for(size_t j=0; j<dirList.size();j++)
	{
		string strDir= dirPathStr + dirList[j];
		string strNewSubDir = strDir;
		strDir= strDir+"/";
		KeyStr kSubDirTreeDir(strDir);
		strDir= strDir+END_DIRECTORY;

		KeyStr kSubDir(strDir);
		ValueInt vSubDir(0);
		if(!imgTree.exists(kSubDir))
		{
			imgTree.insert(kSubDir,vSubDir);
		}
		if(!dirTree.exists(kSubDirTreeDir))
		{
			ans.push_back(strNewSubDir);
			ValueNull vNull;
			dirTree.insert(kSubDirTreeDir,vNull);
		}
	}
	return ans;
}
/* -------------------------------------------------------------------------- */
string ImageManager::GetPathImage(ID_type idImg)
{
	ImgRegistry* imgReg = (ImgRegistry*)orgImages.GetRegistry(idImg);
	if(imgReg == NULL )
		return NULL;
	string path = orgNamesImages.GetText(imgReg->GetIDImagePath());
	return path;
}
/* -------------------------------------------------------------------------- */
void ImageManager::RecorreElArbol(){
	if(imgTree.empty())
		return;

	KeyStr kDir("");
	TreeIterator& it = imgTree.first();
	while (!it.end()){
		KeyStr* kStr=(KeyStr*)it.getKey();
		string pathFile=(kStr->getKey());
		cout<<pathFile<<endl;
		delete kStr;
		++it;
	}
	imgTree.deleteIterator(it);

}
/* -------------------------------------------------------------------------- */
void ImageManager::RecorreElArbolDir(){
	if(dirTree.empty())
			return;
	KeyStr kDir("");
	TreeIterator& it = dirTree.first();
	while (!it.end()){
		KeyStr* kStr=(KeyStr*)it.getKey();
		string pathFile=(kStr->getKey());
		cout<<pathFile<<endl;
		delete kStr;
		++it;
	}
	dirTree.deleteIterator(it);
}
/* -------------------------------------------------------------------------- */

void ImageManager::TransformKeyImgToKeyDir(string& st){
	tVecStr vStr=StrToken::getStrTokens(st,"/");
	string staux="";
	staux.append(st.c_str(),st.length()-3);
	st=staux;
}
/* -------------------------------------------------------------------------- */

tVecStr ImageManager::DeleteDirectory(const char* dirPath){
	bool end=false;

	string dir=string (dirPath);
	tVecStr fileList=FileSystem::GetFiles(dirPath,File);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	StrToken::FormatPath(dir);

	KeyStr kDirDir(dir);
	dir.append(END_DIRECTORY);
	KeyStr kDir(dir.c_str());
	vector<string> vkFile;
	vector<string> vkDir;
	tVecStr ans;

	if ( (dirTree.empty()) || (!dirTree.exists(kDirDir)))
		return ans;

	TreeIterator& it = imgTree.iterator(kDir);
	while ( (!it.end()) && (end==false) )
	{
		KeyStr* kStr=dynamic_cast<KeyStr*>(it.getKey());
		string pathFile=(kStr->getKey());
		tVecStr tokens=StrToken::getStrTokens(kStr->getKey(),"/");
		if ((strcmp(tokens[tokens.size()-1].c_str(),END_DIRECTORY)) )
		{
			ValueInt* vInt=(ValueInt*)it.getValue();
			DeleteImage(vInt->getValue(),NULL,true,false);
			string pathFile=(kStr->getKey());
			vkFile.push_back(kStr->getKey());
			delete vInt;
		}
		else if (isSubDirectoryOrSubFile(&tokensDir,&tokens)||(!strcmp(dir.c_str(),(kStr->getKey()).c_str())))
		{
			string strDir=kStr->getKey();
			TransformKeyImgToKeyDir(strDir);
			ans.push_back(strDir);
			vkDir.push_back(strDir);
		}
		else
		{
			end=true;
		}
		delete kStr;
		++it;
	}
	imgTree.deleteIterator(it);
	for(unsigned int u=0;u<vkDir.size();u++)
	{
		string path=vkDir[u];
		KeyStr keyDir(path);
		string pathDi=path +END_DIRECTORY;
		KeyStr keyImg(pathDi);
		dirTree.remove(keyDir);
		if (imgTree.exists(keyImg)) //Esto para debuggear
			imgTree.remove(keyImg);
	}
	for(unsigned int u=0;u<vkFile.size();u++)
	{
		string k=vkFile[u];
		KeyStr key(k);
		imgTree.remove(key);
	}
	return ans;
}

/* -------------------------------------------------------------------------- */
bool ImageManager::isSubDirectoryOrSubFile(tVecStr* dir,tVecStr* unknow){
	if (unknow->size()-dir->size()==1){
		if (!strcmp(((*unknow)[unknow->size()-1]).c_str(),END_DIRECTORY))
			return false;
		else
			return true;
	}else if (unknow->size()-dir->size()>1)
		return true;
	else
		return false;
}

/* -------------------------------------------------------------------------- */
void ImageManager::TestDirectory(const char* dirPath){
	tVecStr fileList=FileSystem::GetFiles(dirPath,All);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
	if (imgTree.empty())
		return;
	TreeIterator& it = imgTree.iterator(kDir);
	while (!it.end()){
		KeyStr* k=(KeyStr*)it.getKey();
		cout<<k->getKey()<<endl;
		delete k;
		++it;
	}
	imgTree.deleteIterator(it);
}
/* -------------------------------------------------------------------------- */
tVecStr ImageManager::GetAllDirectories(){
	tVecStr ans;
	if (!dirTree.empty()){
		TreeIterator& it = dirTree.first();
		std::list <std::string> dirList;
		/*
		 * Se obtiene un list (dirList) que contiene los directorios
		 * almacenados en el árbol B.
		 */
		while (!it.end()){
			KeyStr* key=dynamic_cast<KeyStr*>(it.getKey());
			size_t i = key->getKey().rfind('/', key->getKey().length());
			dirList.push_back ( key->getKey().substr( 0, i ) );
			delete key;
			++it;
		}
		dirTree.deleteIterator(it);
		
		// Se eliminan los nombres repetidos
		dirList.unique();

		std::list <std::string> ::iterator itList;
		for ( itList = dirList.begin() ; itList != dirList.end(); itList++ )
			ans.push_back ( *itList );
		dirList.clear();
	}
	return ans;
}

tVecStr ImageManager::filterByDate ( tVecStr list , BppTree & tree )
{
	TreeIterator& it = tree.first();

	while ( !it.end() )
	{
		KeyStr* key = dynamic_cast<KeyStr*>(it.getKey());
		if( imgTree.exists( *key ) )
		{
			ValueInt* idImg = dynamic_cast<ValueInt*>( imgTree.find( *key ));
			if( idImg != NULL )
			{
				ImgRegistry* reg=dynamic_cast<ImgRegistry*>(orgImages.GetRegistry(idImg->getValue()));
				Date d = reg->GetDate();
				if (! ( d == Date::getDate( key->getKey().c_str()) ))
				{
					list.push_back( key->getKey() );
				}
			}
			delete idImg;
		}
		delete key;
		++it;
	}
	tree.deleteIterator(it);
	return list;
}

/* -------------------------------------------------------------------------- */
tVecStr ImageManager::GetMergedList( BppTree & first ,	BppTree & second )
{
	tVecStr  updatedList;
	TreeIterator& it = first.first();

	while (  !it.end() )
	{
		KeyStr* kf = (KeyStr*)it.getKey();
		std::string file ( kf->getKey() );
		size_t i = file.rfind( END_DIRECTORY, file.length());
		if ( ( i == std::string::npos ) && ( !second.exists( *kf ) ) )
				updatedList.push_back( file );
		delete kf;
		++it;
	}
	first.deleteIterator(it);
	return updatedList;
}
/* -------------------------------------------------------------------------- */
tVecStr* ImageManager::GetUpdatedList( IMMode mode )
{
	tVecStr* updatedList = new tVecStr();
	tVecStr tmpList;
	if ( !imgTree.empty() )
	{
		  BppTree* localTree = new BppTree(512,KeyStrFactory(), ValueNullFactory(),PATH_TREE_TMP);

		  //  Se obtiene una lista de todos los paths del B Tree.
		  tVecStr allDirs = GetAllDirectories();


		  //  Se carga un B Tree temprarl con las imagenes a actualizar.
		  for ( unsigned int j = 0; j < allDirs.size() ; j++ )
		  {
		      std::string path = allDirs[j] + "/";
		      tVecStr imgList = FileSystem::GetFiles( path.c_str() , File);
		      if ( imgList.size() != 0 )
		      {
		    	  for ( unsigned int i = 0; i < imgList.size() ; i++ )
		    	  {
		    	   	KeyStr ktmp ( path + imgList[i] );
		    	   	ValueInt vtmp (i);
		    	   	localTree->insert(ktmp,vtmp);
		    	  }
		      }
		      imgList.clear();
		  }
		  switch ( mode )
		  {
			  case Erased: tmpList = GetMergedList( imgTree , *localTree);
						   break;
			  case Added: tmpList = GetMergedList( *localTree , imgTree );
						  break;
			  default: break;
		  }

		  tmpList = filterByDate ( tmpList , *localTree );

		  /*
		   * Se le agregan a updatedList las imagenes que faltan, obtenidas
		   * previamente de la sublista tmpList.
		   */
		  for ( unsigned int i = 0; i < tmpList.size() ; i++ )
			  updatedList->push_back( tmpList[i] );

		  // Se liberan recursos temporales.

		  tmpList.clear();
		  delete localTree;
		  remove (PATH_TREE_TMP);
		  remove (PATH_TREE_TMP_BIG_REGS);
		  allDirs.clear();
	}

	return updatedList;
}
/* -------------------------------------------------------------------------- */
ID_type ImageManager::GetIDImage(const char* path){
	if(imgTree.empty())
		return 0;
	ID_type ans;
	KeyStr key(path);
	if (!imgTree.exists(key))
		return 0;
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
void ImageManager::AddMessageToImage( ID_type idImage, ID_type idMessage)
{
	//Leo el registro imagen para obtener el id del primer registro de la lista de msgs.
	ImgRegistry *imgRegistry = this->GetImageRegistry(idImage);
	if( imgRegistry == NULL )
		throw eFile(PATH_IMG_FILE);
	ID_type firstList = imgRegistry->GetPtrMsgList();
	ListMsgRegistry msgRegistry(idMessage);
	try
	{
		//Si la lista esta vacia, la creo
		if( firstList == 0 )
			this->orgListMsgs.CreateList( msgRegistry);
		else //Si no esta vacia, agrego el nuevo registro al principio
			this->orgListMsgs.AddToListFirst(msgRegistry, firstList);
	}
	catch(char * error){
		throw eFile(PATH_MSG_LIST_FILE);
	}
	//Actualizo el PtrMsgList del registro imagen
	imgRegistry->SetPtrMsgList(msgRegistry.GetID());
	this->UpdateImageRegistry(imgRegistry);

	delete imgRegistry;
}
/* -------------------------------------------------------------------------- */
void ImageManager::RemoveMessageToImage( ID_type idImage, ID_type idMessage)
{
	//Leo el registro imagen para obtener el id del primer registro de la lista de msgs.
	ImgRegistry * imgReg = this->GetImageRegistry(idImage);
	if( imgReg == NULL )
		throw eFile(PATH_IMG_FILE);
	ID_type firstList = imgReg->GetPtrMsgList();
	
	//verifica si la lista no esta vacia.
	if( firstList == 0 )
		return;
	try
	{
		//Eliminar de la lista de mensajes de la imagen, el mensaje especifico.
		tRegisterList* msgList = this->orgListMsgs.GetList(firstList);
		itRegisterList it = msgList->begin();
		ID_type idRegMsgToErase=0;
		ListMsgRegistry* msgReg=NULL;
		//Si la lista no esta vacia, asigno el puntero al nuevo mensaje.
		if( msgList->size() > 1 )
		{
			//Busco el nuevo mensaje de la lista. 
			while(it != msgList->end())
			{
				msgReg = dynamic_cast<ListMsgRegistry*>(*it);
				ID_type msgRegId = msgReg->GetIDMessage();

				if( msgRegId == idMessage )
				{
					idRegMsgToErase = msgReg->GetID();
					if( msgReg->GetID() == imgReg->GetPtrMsgList())
					{
						imgReg->SetPtrMsgList(msgReg->GetNextID());
					}
					break;
				}
				it++;
			}
		}
		else //Si esta vacia, apunta a NULL
		{
			msgReg = dynamic_cast<ListMsgRegistry*>(*it);
			idRegMsgToErase = msgReg->GetID();
			imgReg->SetPtrMsgList(NULL);
		}

		this->orgListMsgs.DeleteFromList(idRegMsgToErase);
		UpdateImageRegistry(imgReg);
		delete imgReg;
	}
	catch(char * error){
		throw eFile(PATH_MSG_LIST_FILE);
	}
}
/* -------------------------------------------------------------------------- */
ImgRegistry* ImageManager::GetImageRegistry( ID_type idImage)
{
	ImgRegistry *imgRegistry = dynamic_cast<ImgRegistry*>(this->orgImages.GetRegistry(idImage));
	return imgRegistry;
}
/* -------------------------------------------------------------------------- */
void ImageManager::UpdateImageRegistry(ImgRegistry* modifiedImgReg)
{
	this->orgImages.UpdateRegistry(*modifiedImgReg);
}
/* -------------------------------------------------------------------------- */

unsigned int ImageManager::GetBitsLsb(const char* filePath)
{
	Image* image = ImageFactory::GetImage(filePath);
	unsigned int bitsLsb = image->GetBitsLsb();
	delete image;
	return bitsLsb;
}



