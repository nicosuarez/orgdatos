#include "FreeSpaceManager.h"

FreeSpaceManager* FreeSpaceManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


FreeSpaceManager::FreeSpaceManager() :  //orgFreeSpaces(PATH_FREE_SPACE_FILE, FreeSpaceRegistry::Create),
	 									orgListFreeSpaces(PATH_FREE_SPACE_FILE, ListFreeSpaceRegistry::Create),
										freeSpacesTree(512,KeyFreeSpaceFactory(), ValueFreeSpaceFactory(),PATH_TREE_FREE_SPACE)
{
}
/* -------------------------------------------------------------------------- */


FreeSpaceManager* FreeSpaceManager::GetInstance()
{
	if(instance == NULL)
		instance = new FreeSpaceManager();
	return instance;
}
/* -------------------------------------------------------------------------- */
FreeSpaceManager::~FreeSpaceManager()
{

}
/* -------------------------------------------------------------------------- */
void FreeSpaceManager::PrintIteratorValue(TreeIterator& it){
	std::pair<Register*,Register*>keyval= *it;

	if(keyval.first){
		keyval.first->toOstream(std::cout);
		delete keyval.first;
	}


	if(keyval.second){
		keyval.second->toOstream(std::cout);
		delete keyval.second;
	}
}
/* -------------------------------------------------------------------------- */
tListSpaces* FreeSpaceManager::GetFreeSpaces(unsigned long msgSize)
{
	//Chequeo si hay espacios libres en el arbol
	if( freeSpacesTree.empty() )
	{
		return NULL;
	}
	unsigned long acumSize=0, position=0, spaceSize=0, newFreeSize=msgSize;
	ID_type imgID=0, freeSpaceID=0;
	tListSpaces * freeSpaceLst = new tListSpaces();
	ImageManager* iManager=ImageManager::GetInstance();
	TreeIterator& it = freeSpacesTree.first();
	tVecFreeSpace deleteKeys, addSpaceKeys;
	
	while(!it.end() && (acumSize < msgSize))
	{
		std::pair<Register*,Register*>keyval= *it;

		KeyFreeSpace* key = dynamic_cast<KeyFreeSpace*>(keyval.first);
		ValueFreeSpace* val = dynamic_cast<ValueFreeSpace*>(keyval.second);

		std::pair<ID_type,unsigned long> keyPair = key->GetKey();
		std::pair<ID_type,unsigned long> valPair = val->GetValue();

		imgID = valPair.first;
		freeSpaceID = keyPair.first;
		spaceSize = keyPair.second;
		position = valPair.second;
		string pathImg; 
		try{
			pathImg= iManager->GetPathImage(imgID);
		}
		catch(char *error){
			throw eFile(PATH_IMG_FILE);
		}

		Space* space = new Space(freeSpaceID, imgID, pathImg, position, spaceSize);
		freeSpaceLst->push_back(space);
		acumSize += spaceSize;

		//Dar de baja el espacio libre, y dar de alta el nuevo espacio libre sobrante.
		deleteKeys.push_back(space);
		
		if(acumSize <= msgSize)
		{
			//Tamano del nuevo espacio libre generado.
			newFreeSize -= spaceSize;
		}
		else
		{
			//Dar de alta el espacio libre nuevo.
			unsigned long newSize = spaceSize - newFreeSize;
			Image* image = ImageFactory::GetImage(pathImg.c_str());
			unsigned int bitsLsb = image->GetBitsLsb();
			unsigned long newPosition = position + newFreeSize * (8/bitsLsb);
			Space* newSpace = new Space(pathImg,newPosition,newSize);
			newSpace->SetIDImage(imgID);
			addSpaceKeys.push_back(newSpace);
		}

//		PrintIteratorValue(it);
		++it;

		//delete key;
		delete val;
	}
	if(it.end() && (acumSize < msgSize))
	{
		freeSpacesTree.deleteIterator(it);
		throw eNotSpace(ERR_INSUFFICIENT_SPACE);
	}
	freeSpacesTree.deleteIterator(it);

	RemoveFreeSpace(deleteKeys);

	for(unsigned int j=0; j<addSpaceKeys.size();j++){
		Space* space = addSpaceKeys[j];
		AddFreeSpace(space);
		delete space;
	}
	return freeSpaceLst;

}
/* -------------------------------------------------------------------------- */
void FreeSpaceManager::RemoveFreeSpace(tVecFreeSpace& freeSpaceList)
{
	for(size_t i=0; i<freeSpaceList.size();i++)
	{
		Space* space = freeSpaceList[i];
		RemoveFreeSpace(space);
	}
}
/* -------------------------------------------------------------------------- */
void FreeSpaceManager::RemoveFreeSpaceList(ID_type ptrFreeSpace)
{
	tRegisterList* freeSpaceList = GetFreeSpacesList(ptrFreeSpace);
	
	itRegisterList it = freeSpaceList->begin();
	while(it != freeSpaceList->end())
	{
		ListFreeSpaceRegistry* fsReg = dynamic_cast<ListFreeSpaceRegistry*>(*it);
		Space* space = new Space(fsReg->GetID(),fsReg->GetIdImage(), fsReg->GetSpaceSize());
		RemoveFreeSpace(space);
		it++;
	}
}
/* -------------------------------------------------------------------------- */
void FreeSpaceManager::RemoveFreeSpace(Space* freeSpace)
{
	ImageManager* iManager=ImageManager::GetInstance();

	ID_type idImage = freeSpace->GetIDImage();
	
	//Leo el registro imagen para obtener el id del primer registro de la 
	//lista de espacios libres.
	ImgRegistry *imgRegistry = iManager->GetImageRegistry(idImage);
	ID_type firstList = imgRegistry->GetPtrFreeSpaceList();
	
	//Eliminar de la lista de la imagen el espacio libre.
	tRegisterList* freeSpaceList = this->orgListFreeSpaces.GetList(firstList);
		
	//Si la lista no esta vacia, asigno el puntero al nuevo espacio libre
	if( freeSpaceList->size() > 1 )
	{
		
//		//Busco el nuevo primer espacio libre de la lista. 
//		while(it != freeSpaceList->end())
//		{
//			ListFreeSpaceRegistry* fsReg = dynamic_cast<ListFreeSpaceRegistry*>(*it);
//			ID_type freeSpacesID = fsReg->GetID();
//			if(freeSpacesID != freeSpace->GetIDSpace())
//			{
//				imgRegistry->SetPtrFreeSpaceList(fsReg->GetID()); 
//				break;
//			}
//			
//			it++;
//		}
		ListFreeSpaceRegistry* fsReg = dynamic_cast<ListFreeSpaceRegistry*>(*freeSpaceList->begin());
		if( freeSpace->GetIDSpace() == firstList )
		{
			imgRegistry->SetPtrFreeSpaceList(fsReg->GetNextID());
		}
		
	}
	else //Si esta vacia, apunta a NULL
	{
		imgRegistry->SetPtrFreeSpaceList(NULL); 
	}

	this->orgListFreeSpaces.DeleteFromList(freeSpace->GetIDSpace());
	
	iManager->UpdateImageRegistry(imgRegistry);

	delete imgRegistry;

	itRegisterList itDel = freeSpaceList->begin();
	while(itDel != freeSpaceList->end())
	{
		delete (*itDel);
		itDel++;
	}
	delete freeSpaceList;

	//Eliminar del arbol
	KeyFreeSpace key(freeSpace->GetIDSpace(), freeSpace->GetSize());
	freeSpacesTree.remove(key);
}
/* -------------------------------------------------------------------------- */

tRegisterList* FreeSpaceManager::GetFreeSpacesList(ID_type ptrFreeSpace)
{
	tRegisterList* fsList=new tRegisterList;
	if(ptrFreeSpace > 0)
	{
		fsList = this->orgListFreeSpaces.GetList(ptrFreeSpace);
	}
	return fsList;
}
/* -------------------------------------------------------------------------- */

void FreeSpaceManager::AddFreeSpaces(tListSpaces* spacesList)
{
	itListSpaces it = spacesList->begin();
	for(it = spacesList->begin(); it != spacesList->end(); it++ )
	{
		Space* space = *it;
		AddFreeSpace(space);
    }
}
/* -------------------------------------------------------------------------- */
ID_type FreeSpaceManager::AddFreeSpace(Space* space)
{
		//Obtengo el imageManager
        ImageManager* iManager=ImageManager::GetInstance();

        ID_type idImage = space->GetIDImage();
        unsigned long spaceSize = space->GetSize();
        unsigned long newPosition = 0;
        unsigned long newSpaceSize = 0;

        //Leo el registro imagen para obtener el id del primer registro de la
        //lista de espacios libres.
        ImgRegistry *imgRegistry = iManager->GetImageRegistry(idImage);
        ID_type firstList = imgRegistry->GetPtrFreeSpaceList();
        ListFreeSpaceRegistry *fsReg = NULL;
       
        //Si la lista esta vacia, la creo
        if( firstList == 0 )
        {
                newSpaceSize = spaceSize;
                newPosition = space->GetInitialPosition();
                fsReg = new ListFreeSpaceRegistry(idImage, newSpaceSize);
                this->orgListFreeSpaces.CreateList((*fsReg));
        }
        else //Si no esta vacia, agrego el espacio al principio
        {
			  tRegisterList* freeSpaceList = this->orgListFreeSpaces.GetList(firstList);
    		  
			  //busco si hay espacios consecutivos al que quiero agregar
			  fsReg = FindSpaceConsecutive( freeSpaceList, space, newPosition, newSpaceSize);
			  
			  //Vuelvo a leer el registro imagen para ver si cambio el campo PtrFreeSpaceList
			  delete imgRegistry;
			  imgRegistry = iManager->GetImageRegistry(idImage);
        	  firstList = imgRegistry->GetPtrFreeSpaceList();
        	  if( firstList == 0 )
        		  this->orgListFreeSpaces.CreateList((*fsReg));
        	  else
        		  this->orgListFreeSpaces.AddToListFirst((*fsReg), firstList);
        }
        //Actualizo el PtrFreeSpaceList del registro imagen
        imgRegistry->SetPtrFreeSpaceList(fsReg->GetID());
        iManager->UpdateImageRegistry(imgRegistry);
        delete imgRegistry;
       
        //Actualizo el arbol de espacios libres.
        KeyFreeSpace keyFs(fsReg->GetID(), newSpaceSize);
        ValueFreeSpace valFs(idImage, newPosition);
        freeSpacesTree.insert(keyFs, valFs);

	   ID_type idSpace = fsReg->GetID();
       delete fsReg;        
       return idSpace;
}
/* -------------------------------------------------------------------------- */


ListFreeSpaceRegistry* FreeSpaceManager::FindSpaceConsecutive(tRegisterList* freeSpaceList, Space* space, unsigned long &newPosition, unsigned long &newSpaceSize)
{
      itRegisterList it = freeSpaceList->begin();
	  Space *before=NULL, *after=NULL;
	  ListFreeSpaceRegistry *fsReg;
      unsigned long idImage = 0;
      unsigned long spaceSize = 0;
      unsigned long position = 0;
	  for(it = freeSpaceList->begin(); it != freeSpaceList->end(); it++)
	  {
		  	fsReg = dynamic_cast<ListFreeSpaceRegistry*>(*it);
		  	ID_type fsId = fsReg->GetID();
		  	KeyFreeSpace keyFind( fsId, fsReg->GetSpaceSize() );
			delete fsReg;
		  	TreeIterator& it = freeSpacesTree.iterator(keyFind);
		  	std::pair<Register*,Register*>keyval= *it;

            KeyFreeSpace* key = dynamic_cast<KeyFreeSpace*>(keyval.first);
            ValueFreeSpace* val = dynamic_cast<ValueFreeSpace*>(keyval.second);

            std::pair<ID_type,unsigned long> keyPair = key->GetKey();
            std::pair<ID_type,unsigned long> valPair = val->GetValue();

            
            idImage = valPair.first;
            spaceSize = keyPair.second;
            position = valPair.second;
		  	unsigned int bitsLsb = ImageManager::GetInstance()->GetBitsLsb(space->GetFilePath());
	  		unsigned int beforePosition = position + spaceSize*(8/bitsLsb);
		  	unsigned int actualPosition = space->GetInitialPosition()  + space->GetSize()*(8/bitsLsb);
	  		if( beforePosition == space->GetInitialPosition() )
	  		{
	  			before = new Space(fsId, idImage, position, spaceSize);
	  		}
		  	else if( position ==  actualPosition)
		  	{
	  			after = new Space( fsId, idImage, position, spaceSize);
		  	}						
	 		if( (before != NULL) && (after != NULL) )
	 			break;
	  }
	  if( (before != NULL) && (after != NULL) ) //Hay espacios consecutivos anterior y posterior
	  {
			newPosition = before->GetInitialPosition();
			newSpaceSize = before->GetSize() + after->GetSize() + space->GetSize(); 
			fsReg = new ListFreeSpaceRegistry(idImage, newSpaceSize);
			RemoveFreeSpace(before);
	  		RemoveFreeSpace(after);
	  		delete before;
	  		delete after;
	  }
	  else if( (before != NULL) && (after == NULL) ) //Hay espacio consecutivo anterior
	  {
			newPosition = before->GetInitialPosition();
			newSpaceSize = before->GetSize() + space->GetSize(); 
			fsReg = new ListFreeSpaceRegistry(idImage, newSpaceSize);
			RemoveFreeSpace(before);
	  		delete before;
	  }
	  else if( (after != NULL) && (before == NULL) ) //Hay espacio consecutivo posterior
	  {
			newPosition = space->GetInitialPosition();
			newSpaceSize = after->GetSize() + space->GetSize(); 
			fsReg = new ListFreeSpaceRegistry(idImage, newSpaceSize);
	  		RemoveFreeSpace(after);
	  		delete after;
	  }
	  else //No hay espacios libres consecutivos
	  {
			newPosition = space->GetInitialPosition();
			newSpaceSize = space->GetSize(); 
			fsReg = new ListFreeSpaceRegistry(idImage, newSpaceSize);
	  }
	  return fsReg;
}
/* -------------------------------------------------------------------------- */


/*void FreeSpaceManager::AddFreeSpaceTree(ID_type idFreeSpace, unsigned long size,
			ID_type idImg, unsigned long position)
{
	KeyFreeSpace keyFs(idFreeSpace, size);
	ValueFreeSpace valFs(idImg, position);
	freeSpacesTree.insert(keyFs, valFs);

	cout << freeSpacesTree << "\n";
}*/
/* -------------------------------------------------------------------------- */

