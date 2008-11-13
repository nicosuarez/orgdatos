///////////////////////////////////////////////////////////
//  FreeSpaceManager.cpp
//  Implementation of the Class FreeSpaceManager
//  Created on:      13-Oct-2008 2:49:30 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "FreeSpaceManager.h"

FreeSpaceManager* FreeSpaceManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


FreeSpaceManager::FreeSpaceManager()
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


list<Space>* FreeSpaceManager::GetFreeSpace(int size)
{
		return  NULL;
}
/* -------------------------------------------------------------------------- */
