/*
 * WordsManager.cpp
 *
 */

#include "WordsManager.h"

WordsManager* WordsManager::instance = NULL;

WordsManager::WordsManager(): orgWords(PATH_FILE_WORDS, WordRegistry::Create),
							  orgListSets(PATH_FILE_LIST_SETS, ListSetsRegistry::Create),
							  treeWords(512, KeyStrFactory(), ValueIntFactory(), PATH_TREE_WORDS)
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


ID_type WordsManager::addWord(ustring word)
{
	//Chequeo si la palabra ya existe en el arbol
	KeyStr key(word);
	if( treeWords.exists(key) )
		return -1;

	//Agrego un nuevo registro a orgWords
	ExtensibleRelativeRegistry *reg = new WordRegistry();
	orgWords.WriteRegistry(*reg);
	ID_type idReg = reg->GetID();
	//Si el registro se pudo agregar, inserto la palabra en el arbol
	if(idReg>0)
	{
		ValueInt value(reg->GetID());
		treeWords.insert(key, value);
	}
	delete reg;
	return idReg;
}


void WordsManager::addSetToWord(ID_type idWord, ID_type idSet)
{
	WordRegistry *reg = dynamic_cast<WordRegistry*>(orgWords.GetRegistry(idWord));
	ListSetsRegistry *regList = NULL;
	if(reg==NULL)
		return;

	//Si no tiene lista de sets agrego una nueva lista
	if( reg->GetIdListSets() == 0)
	{
		regList = new ListSetsRegistry();
		unsigned int idInitial = (idSet/32)*32+1;
		regList->SetIdInitial(idInitial);
		regList->AddIdSet(idSet);
		orgListSets.CreateList(*regList);
		reg->SetIdListSets(regList->GetID());
	}
	else
	{

	}
	orgWords.UpdateRegistry(*reg);
	delete reg;
	delete regList;
}


list<ID_type>* WordsManager::getSets(ID_type idWord)
{
	return NULL;
}
