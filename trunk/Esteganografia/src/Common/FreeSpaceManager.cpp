#include "FreeSpaceManager.h"

FreeSpaceManager* FreeSpaceManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


FreeSpaceManager::FreeSpaceManager()
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


list<Space>* FreeSpaceManager::GetFreeSpace(int size)
{
		return  NULL;
}
/* -------------------------------------------------------------------------- */
