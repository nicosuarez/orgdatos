/*
 * SetsManager.cpp

 */

#include "SetsManager.h"
#include <iostream>
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

long int getSizeFile(std::string path)
{
	ifstream arch2;
	arch2.open(PATH_FILE_LIST_WORDS);
	arch2.seekg(0,std::ios::end);
	long int offset = arch2.tellg();
	arch2.close();
	return offset;
}

ID_type SetsManager::addSet( list<ustring> *listWords) {
//	listWords.sort();
	long int offset = getSizeFile(PATH_FILE_LIST_WORDS);
	list<ustring>::iterator it;
	ofstream arch;
	if(offset < 0)
	{
		arch.open(PATH_FILE_LIST_WORDS, std::ios::out);
		offset = 0;
	}
	else
		arch.open(PATH_FILE_LIST_WORDS, std::ios::app);
	arch << listWords->size() << '|';
	for( it = listWords->begin(); it != listWords->end(); it++ )
	{
			arch << (*it).size() << (*it).raw();
	}
	arch.flush();
	arch.close();
	SetRegistry reg(offset);
	orgSets.WriteRegistry(reg);
	return reg.GetID();
}

list<ustring>* SetsManager::getList (long int offset, string &cant, ifstream &arch) {
	long int cantDePalabras = atol ( cant.c_str() );
	long int cantDeLetras = 0, cantDePalabrasLeidas = 0;
	list<ustring>* listWs = new list<ustring>;
	arch.seekg(offset, std::ios::beg);
	while (cantDePalabrasLeidas < cantDePalabras) {
		arch >> cantDeLetras;
		ustring palabra;
		char byte;
		for (long int j = 0; j<cantDeLetras ;j++)
		{
			arch >> std::noskipws >> byte;
					palabra.insert(j,1,byte);
		}
		cantDePalabrasLeidas++;
		listWs->push_back( palabra );
	}
	return listWs;
}

ID_type SetsManager::addSet()
{
	return ++count;
}


list<ustring>* SetsManager::getSet(ID_type idSet) {
	SetRegistry *reg;
	try{
		reg = dynamic_cast<SetRegistry*>(this->orgSets.GetRegistry(idSet));
	}
	catch(...)
	{
		return NULL;
	}
	if (reg != NULL) {
		long int offset = reg->GetOffsetListWords();
		string str;
		char byte;
		ifstream arch;
		arch.open(PATH_FILE_LIST_WORDS);
		arch.seekg(offset, std::ios::beg);
		arch >> byte;
		long int pos = 0;
		while ( byte != '|')
		{
			str.insert (pos,1, byte);
			pos++;
			arch >> byte;
		}
		list<ustring>* listaWords = getList(offset+pos+1, str, arch);
		arch.close();
		delete reg;
		return listaWords;
	}
	return NULL;
}
