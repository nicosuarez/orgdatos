/*
 * main.cpp
 *
 */
#include "Common/WordsManager.h"
#include "Common/BlackWordsManager.h"
#include <string>
#include "WikiArticlesParser/WikiArticlesParser.h"
#include <fstream>

std::string intToString( int entero )
{

    std::stringstream cadena("");
    cadena << entero;
    return cadena.str();
}

void testWordsManager()
{
	WordsManager *wm = WordsManager::getInstance();
	for(int i=0; i<1000; i++)
	{
		ustring word("HOLA ESTA ES UNA PRUEBA DEL ARBOL PORQUE ME ESTA PINCHANDO LA CONCHA DE LA LORA " + intToString(i));
//		ID_type idWord = wm->addWord(word);
		for(int j=0; j<10; j++)
		{
//			wm->addSetToWord(idWord, j);
			wm->addWord(word, j);
		}
	}
	for(int i=0; i<1000; i++)
	{
		ustring word("HOLA ESTA ES UNA PRUEBA DEL ARBOL PORQUE ME ESTA PINCHANDO LA CONCHA DE LA LORA " + intToString(i));
		ID_type idWord = wm->getIdWord(word);
		std::cout << word << std::endl;
		std::cout << "Lista de Sets:" << std::endl;
		std::cout << "\t";
		list<ID_type>* lista = wm->getSets(idWord);
		if(lista== NULL)
				continue;
		list<ID_type>::iterator it;
		for(it=lista->begin(); it != lista->end(); it++)
		{

			std::cout<< (*it) << " ";
		}
		delete lista;
		std::cout << std::endl;
	}
//	delete wm;
}

void testBlackWordsManager()
{
	list<ustring> *lista = new list<ustring>;
	lista->push_back("Hola");
	lista->push_back("Como");
	lista->push_back("Te");
	lista->push_back("Llamas");
	lista->push_back("Amiguito");
	lista->push_back("Del");
	lista->push_back("Alma");
	BlackWordsManager *bm= BlackWordsManager::getInstance();
	bm->addBlackWordToQuery(lista,"Esta no");
//	bm->addBlackWordToQuery(lista,"Esta tampoco");
	list<ustring>* lista2 = bm->getBlackWords(lista);
	list<ustring>::iterator it;
	for(it=lista2->begin(); it!=lista2->end(); it++)
	{
		std::cout<< (*it) << std::endl;
	}
	delete lista2;
	std::cout << "\nAhora elimino una palabra negra\n";
	bm->removeBlackWordFromQuery(lista,"Esta no");
	lista2 = bm->getBlackWords(lista);
	if(lista2 !=NULL)
	{
		for(it=lista2->begin(); it!=lista2->end(); it++)
		{
			std::cout<< (*it) << std::endl;
		}
		delete lista2;
	}
	delete lista;
	delete bm;
}

void testSetsManager()
{
	list<ustring> *lista = new list<ustring>;
	lista->push_back("Hola");
	lista->push_back("Como");
	lista->push_back("Te");
	lista->push_back("Llamas");
	lista->push_back("Amiguito");
	lista->push_back("Del");
	lista->push_back("Alma");
	SetsManager *sm = SetsManager::getInstance();
	ID_type id = sm->addSet(lista);
	std::cout << id <<std::endl;
	delete lista;
	lista = sm->getSet(id);
	list<ustring>::iterator it;
	for(it=lista->begin(); it!=lista->end(); it++)
	{
		std::cout<< (*it) << std::endl;
	}
	delete lista;
//	delete sm;

}

void testSetsManager2()
{
	list<ustring> *lista = new list<ustring>;
	lista->push_back("Me");
	lista->push_back("Quiero");
	lista->push_back("ir");
	lista->push_back("a");
	lista->push_back("Mi");
	lista->push_back("Casa");
	lista->push_back("ya");
	SetsManager *sm = SetsManager::getInstance();
	ID_type id = sm->addSet(lista);
	std::cout << id <<std::endl;
	delete lista;
	lista = sm->getSet(id);
	list<ustring>::iterator it;
	for(it=lista->begin(); it!=lista->end(); it++)
	{
		std::cout<< (*it) << std::endl;
	}
	delete lista;
	delete sm;

}

int main(int argc, char* argv[])
{
//	testWordsManager();
//	testBlackWordsManager();
	WikiArticlesParser wikiArticlesParser(argv[1]);
	wikiArticlesParser.Parse();
	WikiArticlesParser::parseTxt();
//
//	WordsManager *wm = WordsManager::getInstance();
//	wm->print();
	WikiArticlesParser::print();
//	delete wm;
//	testSetsManager();
//	testSetsManager2();

	return 0;
}
