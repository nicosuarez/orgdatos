/*
 * WordsManager.cpp
 *
 */

#include "WordsManager.h"

WordsManager* WordsManager::instance = NULL;

WordsManager::WordsManager(): orgWords(PATH_FILE_WORDS, WordRegistry::Create),
							  orgListSets(PATH_FILE_LIST_SETS, ListSetsRegistry::Create)
{

}

WordsManager::~WordsManager() {

}

WordsManager* WordsManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new WordsManager();
	}
	return instance;
}


ID_type WordsManager::addWord()
{
	return 0;
}


void WordsManager::addSetToWord(ID_type idWord, ID_type idSet)
{

}


list<ID_type>* WordsManager::getSets(ID_type idWord)
{
	return NULL;
}
