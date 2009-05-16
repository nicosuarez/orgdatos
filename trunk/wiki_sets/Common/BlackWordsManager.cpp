/*
 * BlackWordsManager.cpp
 */

#include "BlackWordsManager.h"

BlackWordsManager* BlackWordsManager::instance = NULL;

/* -------------------------------------------------------------------------- */

BlackWordsManager::BlackWordsManager(): fileListBlackWords(PATH_FILE_LIST_BLACK_WORDS, ListBlackWordRegistry::Create),
										fileBlackWords(PATH_FILE_BLACK_WORDS, PATH_NAME_FILE_BLACK_WORDS),
										treeQueries(512, KeyStrFactory(), ValueIntFactory(), PATH_TREE_BLACK_WORDS)
{

}
/* -------------------------------------------------------------------------- */

BlackWordsManager::~BlackWordsManager() {

}
/* -------------------------------------------------------------------------- */

BlackWordsManager* BlackWordsManager::getInstance()
{
	if(instance == NULL)
			instance = new BlackWordsManager();
	return instance;
}
/* -------------------------------------------------------------------------- */

ustring BlackWordsManager::concatWords(list<ustring> *words)
{
	words->sort();
	list<ustring>::iterator it;
	ustring word("");
	for(it=words->begin(); it!=words->end(); it++)
	{
		word += (*it);
	}
	return word;
}
/* -------------------------------------------------------------------------- */

void BlackWordsManager::addBlackWordToQuery(list<ustring> *query, ustring blackWord)
{
	//Guardo la palabra en la organizacion texto.
	ID_type idBlackWord = fileBlackWords.WriteText(blackWord);
	ListBlackWordRegistry regList(idBlackWord);

	//Busco la query en el arbol
	ustring concatQuery = concatWords(query);
	KeyStr key(concatQuery);
	ValueInt* valueInt = dynamic_cast<ValueInt*>(treeQueries.find(key));
	if(valueInt == NULL)
	{
		//La query no esta en el arbol, entonces creo una nueva lista
		//y agrego la query en el arbol
		fileListBlackWords.CreateList(regList);
		ValueInt newValue(regList.GetID());
		treeQueries.insert(key, newValue);
	}
	else
	{
		//La query ya existe, entonces agrego a la lista una nueva palabra
		//y actualizo el arbol
		ID_type idList = valueInt->getValue();
		fileListBlackWords.AddToListFirst(regList, idList);
		ValueInt newValue(regList.GetID());
		treeQueries.update(key,newValue);
		delete valueInt;
	}
}
/* -------------------------------------------------------------------------- */

void BlackWordsManager::removeBlackWordFromQuery(list<ustring> *query, ustring wordToDelete)
{
	ustring concatQuery = concatWords(query);
	KeyStr key(concatQuery);
	ValueInt* valueInt = dynamic_cast<ValueInt*>(treeQueries.find(key));
	if(valueInt == NULL)
		return;
	ID_type idList = valueInt->getValue();
	delete valueInt;
	if(idList == 0)
		return;
	try
	{
		//Busco en la lista, la palabra a eliminar
		tRegisterList* listWords = fileListBlackWords.GetList(idList);
		if(listWords == NULL)
			return;
		itRegisterList it;
		ListBlackWordRegistry *reg;
		for(it=listWords->begin(); it!=listWords->end(); it++)
		{
			reg = dynamic_cast<ListBlackWordRegistry*>(*it);
			ID_type idCurrentWord = reg->GetIdWord();
			ustring currentWord = fileBlackWords.GetText(idCurrentWord);
			if(currentWord == wordToDelete)
			{
				//Elimino los registros
				fileBlackWords.DeleteText(idCurrentWord);
				fileListBlackWords.DeleteFromList(reg->GetID());

				//Si la palabra que elimine era la primera de la lista, actualizo el arbol
				if(reg->GetID() == idList)
				{
					ValueInt newValueInt(reg->GetNextID());
					treeQueries.update(key, newValueInt);
				}
				break;
			}
		}
		OrgList::FreeList(listWords);
	}
	catch(...)
	{
		return;
	}
}

/* -------------------------------------------------------------------------- */

list<ustring>* BlackWordsManager::getBlackWords(list<ustring> *query)
{
	ustring concatQuery = concatWords(query);
	KeyStr key(concatQuery);
	ValueInt *value = dynamic_cast<ValueInt*>(treeQueries.find(key));
	if(value == NULL)
	{
		return NULL;
	}
	try
	{
		tRegisterList* listIdWords = fileListBlackWords.GetList(value->getValue());
		if(listIdWords == NULL)
		{
			delete value;
			return NULL;
		}
		list<ustring> *listWords = new list<ustring>;
		itRegisterList it;
		ListBlackWordRegistry *reg;
		for(it=listIdWords->begin(); it!=listIdWords->end(); it++)
		{
			reg = dynamic_cast<ListBlackWordRegistry*>(*it);
			ustring word = fileBlackWords.GetText(reg->GetIdWord());
			listWords->push_back(word);
		}
		OrgList::FreeList(listIdWords);
		delete value;
		return listWords;
	}
	catch(...)
	{
		delete value;
		return NULL;
	}
}
/* -------------------------------------------------------------------------- */
