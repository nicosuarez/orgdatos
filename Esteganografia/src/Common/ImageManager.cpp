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

unsigned long ImageManager:: totalFreeSize = 0;
ImageManager* ImageManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


ImageManager::ImageManager(): orgImages(PATH_MESSAGE_FILE, ImgRegistry::RegCreate),
							 // orgListFreeSpaces(PATH_FREE_SPACE_FILE, ListFreeSpaceRegistry::Create),
							  orgListMsgs(PATH_MSG_LIST_FILE, ListMsgRegistry::Create),
							  orgNamesImages(PATH_NAMES_IMG_PATHFILE, PATH_NAMES_IMG_FILE),
							  //orgNamesDir(PATH_NAMES_DIR_FILE),
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
	delete instance;
}
/* -------------------------------------------------------------------------- */


void ImageManager::DeleteImage(Image* image){

}
/* -------------------------------------------------------------------------- */


ID_type ImageManager::AddImage(const char* imagePath){

	FreeSpaceManager* fsManager = FreeSpaceManager::GetInstance();
	Image* image = ImageFactory::GetImage(imagePath);
	ImgRegistry imgReg;
	if(image != NULL)
	{
		Space* space = image->Load();
		//Se crea el espacio libre.
		ID_type idFreeSpace = fsManager->AddFreeSpace(space);

		//Guardo el path completo de la imagen.
		ID_type idPath = orgNamesImages.WriteText(space->GetFilePath());

		//Asignar lista de mensajes
		imgReg.SetPtrMsgList(NULL);
		imgReg.SetIDImagePath(idPath);
		Date date = Date::getDate(space->GetFilePath());
		imgReg.SetDate(date);

		//Guardar Imagen
		orgImages.WriteRegistry(imgReg);

		//Actualizo el arbol de imagenes.
		fsManager->AddFreeSpaceTree(idFreeSpace,space->GetSize(),imgReg.GetID(),
								space->GetInitialPosition());

	}

	return imgReg.GetID();
}
/* -------------------------------------------------------------------------- */
/*
 * Agrega todos los directorios y imagenes al arbol imgTree
 * Agrega agrega todas las imagenes al imgFile
 */
tVecStr ImageManager::AddDirectory(const char* dirPath){
	tVecStr ans;
	tVecStr fileList=FileSystem::GetFiles(dirPath,All);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	string strdir=string(dirPath)+ "/";
	KeyStr kDirDir(strdir);
	strdir=strdir+".@";
	KeyStr kDir(strdir);
	ValueInt vDir(0);
	ValueNull vNull;
	dirTree.insert(kDirDir,vNull);
	imgTree.insert(kDir,vDir);
	for(size_t i=0; i<fileList.size();i++){
		string fullPath =string(dirPath)+ "/";
		fullPath= fullPath + fileList[i];
		tVecStr tokensFile=StrToken::getStrTokens(fileList[i].c_str(),"/");
		//es una imagen
		ID_type id =0;
		AddImage(fullPath.c_str());
		KeyStr keyImg(fullPath);
		ValueInt valImg(id);
		this->imgTree.insert(keyImg,valImg);
		std::cout << fullPath << std::endl;
	}
	tVecStr dirList=FileSystem::GetFiles(dirPath,Dir);
	for(size_t j=0; j<dirList.size();j++){
		string strdir=string(dirPath)+"/";
		strdir= strdir + dirList[j];
		ans.push_back(strdir);
		strdir= strdir+"/";
		KeyStr kSubDirTreeDir(strdir);
		strdir= strdir+".@";
		std::cout << strdir << std::endl;
		KeyStr kSubDir(strdir);
		ValueInt vSubDir(0);
		imgTree.insert(kSubDir,vSubDir);
		ValueNull vNull;
		dirTree.insert(kSubDirTreeDir,vNull);
	}
	return ans;

	/*KeyStr other("/home/malcha/Escritorio/Datos/Eclipse/AuxStegno/Estegno/Stegno/Imb");
	ValueInt vother(2);
	imgTree.insert(other,vother);
	cout<<"Recorro el arbol"<<endl;
	RecorreElArbol();
	cout<<"Ahora empiezo a borrar"<<endl;
	DeleteDirectory(dirPath);*/
}
/* -------------------------------------------------------------------------- */
const char* ImageManager::GetPathImage(ID_type idImg)
{
	ImgRegistry* imgReg = (ImgRegistry*)orgImages.GetRegistry(idImg);
	string path = orgNamesImages.GetText(imgReg->GetIDImagePath());
	return path.c_str();
}
/* -------------------------------------------------------------------------- */
void ImageManager::RecorreElArbol(){
	KeyStr kDir("");
	TreeIterator& it = dirTree.iterator(kDir);
	while (!it.end()){
		KeyStr* kStr=(KeyStr*)it.getKey();
		string pathFile=(kStr->getKey());
		cout<<pathFile<<endl;
		delete kStr;
		++it;
	}
}
/* -------------------------------------------------------------------------- */

tVecStr ImageManager::DeleteDirectory(const char* dirPath){
	bool end=false;
	tVecStr fileList=FileSystem::GetFiles(dirPath,All);
	tVecStr tokensDir=StrToken::getStrTokens(dirPath,"/");
	KeyStr kDir(dirPath);
	vector<KeyStr> vkStr;
	vector<KeyStr> vkDir;
	tVecStr ans;
	if (imgTree.empty())
		return ans;
	TreeIterator& it = imgTree.iterator(kDir);
	while ((!it.end())&&(end==false)){
		KeyStr* kStr=(KeyStr*)it.getKey();
		string pathFile=(kStr->getKey());
		tVecStr tokens=StrToken::getStrTokens(pathFile,"/");
		if (!(strcmp(tokens[tokens.size()-1].c_str(),".@")) ){
			ValueInt* vInt=(ValueInt*)it.getValue();
			DeleteImage(vInt->getValue());
			vkStr.push_back(*kStr);
			delete vInt;
		}else if ((tokens.size()-tokensDir.size()>0)||(strcmp(dirPath,pathFile.c_str())==0)){
			ans.push_back(kStr->getKey());
			vkDir.push_back(*kStr);
		}
		else
			end=true;

		delete kStr;
		++it;
	}
	for(unsigned int u=0;u<vkStr.size();u++)
		imgTree.remove(vkStr[u]);
	for(unsigned int u=0;u<vkDir.size();u++){
		imgTree.remove(vkDir[u]);
		dirTree.remove(vkDir[u]);
	}
	//TestDirectory(dirPath);
	return ans;
}

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
		//dirList.sort();
		/*
		 * Se eliminan los directorios repetidos
		 */
		dirList.unique();

		std::list <std::string> ::iterator itList;
		for ( itList = dirList.begin() ; itList != dirList.end(); itList++ )
			ans.push_back ( *itList );

		dirList.clear();
	}
	return ans;
}

/* -------------------------------------------------------------------------- */
tVecStr ImageManager::GetImageErasedList( const std::string & path )
{
	tVecStr  erasedList;

	if ( !imgTree.empty() )
	{
		KeyStr kDir( path ); tVecStr tmpList;
		/*
		 * Se obtiene una lista de nombres de imagenes que se encuentran
		 * en el path en disco.
		 */
		tVecStr imgList = FileSystem::GetFiles( path.c_str() , File);
		TreeIterator& it = imgTree.iterator(kDir);

		/*
		 * Se recorre el imgTree generando una lista (tmpList) de imagenes
		 * de acuerdo a el path.
		 */
		while (  !it.end() )
		{
			KeyStr* key = (KeyStr*)it.getKey();
			size_t i = key->getKey().rfind('/', key->getKey().length());
			if ( ( i != std::string::npos ) &&
				 ( path == key->getKey().substr( 0, i) ) )
				tmpList.push_back( key->getKey().substr( i+1, key->getKey().length()-i));
			delete key;
			++it;
		}
		imgTree.deleteIterator(it);
		/*
		 * Se ordena la lista imgList.
		 */
		sort ( imgList.begin() , imgList.end() );

		for ( unsigned int j = 0; j < tmpList.size() ; j++ )
		{
			/*
			 * Se busca en imgList los archivos cuyo nombre coinciden con los
			 * de tmpList, en el caso de no coincidir se los considera como
			 * recientemente borrados.
			 */
			if ( ! binary_search ( imgList.begin(), imgList.end(), tmpList[j] ) )
				erasedList.push_back( tmpList[j] );
		}
		imgList.clear();
		tmpList.clear();
	}
	return erasedList;
}

/* -------------------------------------------------------------------------- */
tVecStr ImageManager::GetImageErasedFromDirectories()
{
	tVecStr erasedImg;
	tVecStr allDirs = GetAllDirectories();
	for ( unsigned int i = 0; i < allDirs.size(); i++ )
	{
		tVecStr tmpList = GetImageErasedList( allDirs[i] );
		std::string path = allDirs[i] + "/";
		for ( unsigned int i = 0; i < tmpList.size(); i++ )
			erasedImg.push_back( path + tmpList.at(i) );
		tmpList.clear();
	}
	allDirs.clear();

	return erasedImg;
}

/* -------------------------------------------------------------------------- */
void ImageManager::DeleteImage(ID_type id){

}

/* -------------------------------------------------------------------------- */
ID_type ImageManager::GetIDImage(const char* path){
	ID_type ans;
	KeyStr key(path);
	if (imgTree.exists(key))
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

list<Space> ImageManager::GetSpacesToStore(unsigned long sizeMsg)
{
	list<Space> lista;
	return lista;
}

/* -------------------------------------------------------------------------- */

void ImageManager::AddMessageToImage( ID_type idImage, ID_type idMessage)
{
	//Leo el registro imagen para obtener el id del primer registro de la lista de msgs.
	ImgRegistry *imgRegistry = dynamic_cast<ImgRegistry*>(this->orgImages.GetRegistry(idImage));
	ID_type firstList = imgRegistry->GetPtrMsgList();
	ListMsgRegistry msgRegistry(idMessage);

	//Si la lista esta vacia, la creo
	if( firstList == 0 )
	{
		this->orgListMsgs.CreateList( msgRegistry);
	}
	else //Si no esta vacia, agrego el nuevo registro al principio
	{

		this->orgListMsgs.AddToListFirst(msgRegistry, firstList);
	}

	//Actualizo el PtrMsgList del registro imagen
	imgRegistry->SetPtrMsgList(msgRegistry.GetID());

	delete imgRegistry;
}
