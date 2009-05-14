/*
 * WordsManager.cpp
 *
 */

#include "WordsManager.h"

WordsManager* WordsManager::instance = NULL;

/* -------------------------------------------------------------------------- */

WordsManager::WordsManager(): orgWords(PATH_FILE_WORDS, WordRegistry::Create),
							  orgListSets(PATH_FILE_LIST_SETS, ListSetsRegistry::Create),
							  treeWords(512, KeyStrFactory(), ValueIntFactory(), PATH_TREE_WORDS)
{

}
/* -------------------------------------------------------------------------- */

WordsManager::~WordsManager() {

}
/* -------------------------------------------------------------------------- */

WordsManager* WordsManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new WordsManager();
	}
	return instance;
}
/* -------------------------------------------------------------------------- */

ID_type WordsManager::getIdWord(ustring word)
{
	KeyStr key(word);
	ValueInt *vInt = dynamic_cast<ValueInt*>(treeWords.find(key));
	if(vInt != NULL)
		return vInt->getValue();
	else return -1;
}
/* -------------------------------------------------------------------------- */

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
/* -------------------------------------------------------------------------- */

void WordsManager::addSetToWord(ID_type idWord, ID_type idSet)
{
	WordRegistry *regWord;
	try{
		 regWord = dynamic_cast<WordRegistry*>(orgWords.GetRegistry(idWord));
	}
	catch(...)
	{
		return;
	}
	ListSetsRegistry *regList = NULL;
	unsigned int amountByNode = ListSetsRegistry::GetAmountIdByNode();
	unsigned int idInitial = (idSet/amountByNode)*amountByNode+1;

	//Si no tiene lista de sets agrego una nueva lista
	if( regWord->GetIdListSets() == 0)
	{
		regList = new ListSetsRegistry();
		regList->SetIdInitial(idInitial);
		regList->AddIdSet(idSet);
		orgListSets.CreateList(*regList);
		regWord->SetIdListSets(regList->GetID());
		orgWords.UpdateRegistry(*regWord);
		delete regList;
	}
	else
	{
		//Busco en la lista si existe el nodo en el cual se debe guardar el set
		tRegisterList *listSets = orgListSets.GetList(regWord->GetIdListSets());
		itRegisterList it;
		bool found = false;
		for(it = listSets->begin(); it != listSets->end(); it++)
		{
			regList = dynamic_cast<ListSetsRegistry*>(*it);
			if(regList->GetIdInitial() == idInitial)
			{
				regList->AddIdSet(idSet);
				orgListSets.UpdateRegistry(*regList);
				found = true;
				break;
			}
		}
		//Si el nodo no existe, lo agrego al final de la lista
		if(!found)
		{
			regList = new ListSetsRegistry();
			regList->SetIdInitial(idInitial);
			regList->AddIdSet(idSet);
			orgListSets.AddToListLast(*regList, regWord->GetIdListSets());
			delete regList;
		}
		OrgList::FreeList(listSets);
	}
	delete regWord;
}
/* -------------------------------------------------------------------------- */

void WordsManager::addSetToWord(ustring word, ID_type idSet)
{
	addSetToWord(getIdWord(word), idSet);
}
/* -------------------------------------------------------------------------- */
list<ID_type>* WordsManager::getSets(ID_type idWord)
{
	WordRegistry *regWord;
	try
	{
		regWord= dynamic_cast<WordRegistry*>(orgWords.GetRegistry(idWord));
	}
	catch(...)
	{
		return NULL;
	}
	ID_type idList = regWord->GetIdListSets();
	if( idList <= 0)
	{
		delete regWord;
		return NULL;
	}
	tRegisterList *listRegSets = orgListSets.GetList(idList);
	itRegisterList it;
	list<ID_type> *listIdSets = new list<ID_type>, *nodeList;
	for(it = listRegSets->begin(); it != listRegSets->end(); it++)
	{
		ListSetsRegistry *regSets = dynamic_cast<ListSetsRegistry*>(*it);
		nodeList = regSets->GetListSets();
		listIdSets->merge(*nodeList);
		delete nodeList;
	}
	delete regWord;
	OrgList::FreeList(listRegSets);
	return listIdSets;
}
