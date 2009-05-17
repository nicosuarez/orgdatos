/*
 * SetsManager.cpp

 */

#include "SetsManager.h"

SetsManager* SetsManager:: instance = NULL;

SetsManager::SetsManager(): orgSets(PATH_FILE_SETS, SetRegistry::Create), count(0)
{
}

SetsManager::~SetsManager() {

}

SetsManager* SetsManager::getInstance()
{
	if(instance == NULL)
		instance = new SetsManager();
	return instance;
}

ID_type SetsManager::addSet(list<ustring> *listWords)
{

	return 0;
}

ID_type SetsManager::addSet()
{
	return ++count;
}

std::list<ustring>* SetsManager::getSet(ID_type idSet) const
{
	return NULL;
}
