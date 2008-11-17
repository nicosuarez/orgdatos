#include "FreeSpaceManager.h"

FreeSpaceManager* FreeSpaceManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


FreeSpaceManager::FreeSpaceManager() :  orgListFreeSpaces(PATH_FREE_SPACE_FILE, ListFreeSpaceRegistry::Create),
										freeSpacesTree(512,KeyStrFactory(), ValueIntFactory(),PATH_TREE_IMG)
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
tListSpaces* FreeSpaceManager::GetFreeSpaces(unsigned long size)
{
	
	//TreeIterator& it = freeSpacesTree.iterator();
		return  NULL;
}
/* -------------------------------------------------------------------------- */
ID_type AddFreeSpaces(tListSpaces* space)
{
	return 1;
}
/* -------------------------------------------------------------------------- */
ID_type FreeSpaceManager::AddFreeSpace(Space* space)
{
	ListFreeSpaceRegistry fsReg;
	fsReg.SetOffsetImage(space->GetInitialPosition());
	fsReg.SetSizeFreeSpace(space->GetSize());
	orgListFreeSpaces.CreateList(fsReg);
	return fsReg.GetID();	
}
/* -------------------------------------------------------------------------- */
