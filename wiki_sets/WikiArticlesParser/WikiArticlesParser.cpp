/* -------------------------------------------------------------------------- */
// WikiArticlesParser.cpp
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "WikiArticlesParser.h"

WikiArticlesParser::WikiArticlesParser(const ustring &dumpPath)
{
	this->dumpPath = dumpPath;
}

/* -------------------------------------------------------------------------- */

WikiArticlesParser::~WikiArticlesParser()
{
}

/* -------------------------------------------------------------------------- */

void WikiArticlesParser::Parse()
{
	ustring *text = NULL;
	ustring *title = NULL;

	ustring name;
	unsigned depth = 0;

	bool notEmpty = false;
	bool insidePage = false;

	TextReader reader(this->dumpPath);
	TextReader::xmlNodeType nodeType;
#ifdef DEBUG
	unsigned count = 0;
	while(reader.read() && count < DEBUG_ARTICLES_COUNT)
#else
	while(reader.read())
#endif
  {
		nodeType = reader.get_node_type();
		notEmpty = !reader.is_empty_element();

		if (notEmpty && nodeType == TextReader::Element)
		{
			name = reader.get_name();
			depth = reader.get_depth();

		  if (depth == PAGE_NODE_DEPTH && name == PAGE_NODE_NAME)
		  {
				insidePage = true;
		  }

		  if (insidePage && depth == TITLE_NODE_DEPTH && name == TITLE_NODE_NAME)
		  {
		  	title = new ustring(reader.read_inner_xml());
		  }

		  if (insidePage && depth == TEXT_NODE_DEPTH && name == TEXT_NODE_NAME)
		  {
		  	text = new ustring(reader.read_inner_xml());
				this->parserManager.Parse(title, text);

				insidePage = false;
#ifdef DEBUG
				++count;
#endif
		  }
		}
  }

  reader.close();
}

std::string WikiArticlesParser::intToString( int entero )
{

    std::stringstream cadena("");
    cadena << entero;
    return cadena.str();
}

void WikiArticlesParser::parseTxt()
{
	ifstream file;
	file.open("./dump/parse_result.txt");
	string linea;
	if(!file.is_open())
		return;
	if(!file.eof())
		getline(file, linea);
	list<ustring>* lista = new list<ustring>;
	SetsManager* sm = SetsManager::getInstance();
	WordsManager *wm = WordsManager::getInstance();
	while(!file.eof())
	{
		getline(file, linea);
		if( linea.size() != 0)
		{
			lista->push_back(linea);
		}
		else
		{
			ID_type idSet = sm->addSet(lista);
			list<ustring>::iterator it;
			int i=0;
			for(it=lista->begin(); it!=lista->end(); it++)
			{
				wm->addWord((*it).raw(), idSet);

//				wm->addWord(intToString(i), idSet);
				i++;
//				std::cout << (*it).raw() << " " << idSet << std::endl;
			}
			lista->clear();
		}

	}
	file.close();
	delete lista;
}

void WikiArticlesParser::print()
{
	ifstream file;
	file.open("./dump/parse_result.txt");
	string linea;
	if(!file.is_open())
		return;
	if(!file.eof())
		getline(file, linea);
	WordsManager *wm = WordsManager::getInstance();
	while(!file.eof())
	{
		getline(file, linea);
		if( wm->getIdWord(linea)<=0)
		{
			std::cout<<"NO ENCONTRO: " << linea << std::endl;
		}
	}
	file.close();
}
