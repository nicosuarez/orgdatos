#include "FreeSpaceManager.h"

FreeSpaceManager* FreeSpaceManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


FreeSpaceManager::FreeSpaceManager() :  orgFreeSpaces(PATH_FREE_SPACE_FILE, FreeSpaceRegistry::Create),
										freeSpacesTree(512,KeyFreeSpaceFactory(), ValueFreeSpaceFactory(),PATH_TREE_FREE_SPACE)
{
	delete instance;
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
tListSpaces* FreeSpaceManager::GetFreeSpaces(unsigned long imgSize)
{
	unsigned long acumSize=0, position=0, spaceSize=0, newFreeSize=imgSize;
	ID_type imgID=0;
	tListSpaces * freeSpaceLst = new tListSpaces();
	ImageManager* iManager=ImageManager::GetInstance();
	TreeIterator& it = freeSpacesTree.first();
	tVecKFreeSpace deleteKeys;
	tVecNewFreeSpaces addSpaceKeys;

	while(!it.end() && (acumSize < imgSize))
	{
		std::pair<Register*,Register*>keyval= *it;

		KeyFreeSpace* key = dynamic_cast<KeyFreeSpace*>(keyval.first);
		ValueFreeSpace* val = dynamic_cast<ValueFreeSpace*>(keyval.second);

		std::pair<ID_type,unsigned long> keyPair = key->GetKey();
		std::pair<ID_type,unsigned long> valPair = val->GetValue();

		imgID = valPair.first;
		spaceSize = keyPair.second;
		position = valPair.second;
		string pathImg = iManager->GetPathImage(imgID);

		Space * space = new Space(pathImg,EMPTY,position,spaceSize);
		freeSpaceLst->push_front(space);
		acumSize += spaceSize;

		//Dar de baja el espacio libre, y dar de alta el nuevo espacio libre sobrante.
		//freeSpacesTree.remove(*key);
		deleteKeys.push_back(key);
		if(acumSize <= imgSize)
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
			Space * newSpace = new Space(pathImg,EMPTY,newPosition,newSize);
			newSpace->SetIDImage(imgID);
			addSpaceKeys.push_back(newSpace);
			//AddFreeSpace(space);
			//delete space;
		}

//		PrintIteratorValue(it);
		++it;

		//delete key;
		delete val;
	}
	if(it.end() && (acumSize < imgSize))
	{
		freeSpacesTree.deleteIterator(it);
		throw eFile(ERR_INSUFFICIENT_SPACE);
	}
	freeSpacesTree.deleteIterator(it);

	for(unsigned int i=0; i<deleteKeys.size();i++){
		freeSpacesTree.remove(*(deleteKeys[i]));
		delete deleteKeys[i];
	}

	for(unsigned int j=0; j<addSpaceKeys.size();j++){
		AddFreeSpace(addSpaceKeys[j]);
		delete addSpaceKeys[j];
	}
	return freeSpaceLst;
}
/* -------------------------------------------------------------------------- */
void FreeSpaceManager::AddFreeSpaces(tListSpaces* spacesList)
{
	itListSpaces it = spacesList->begin();
	for(it = spacesList->begin(); it != spacesList->end(); it++ )
	{
		Space* space = *it;
		AddFreeSpace(space);
		//AddFreeSpaceTree(idFreeSpace, space->GetSize(), idImg ,space->GetInitialPosition());

    };
}
/* -------------------------------------------------------------------------- */
ID_type FreeSpaceManager::AddFreeSpace(Space* space)
{
	FreeSpaceRegistry fsReg;
	orgFreeSpaces.WriteRegistry(fsReg);
	KeyFreeSpace keyFs(fsReg.GetID(), space->GetSize());
	ValueFreeSpace valFs(space->GetIDImage(), space->GetInitialPosition());
	freeSpacesTree.insert(keyFs, valFs);

	return fsReg.GetID();
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

