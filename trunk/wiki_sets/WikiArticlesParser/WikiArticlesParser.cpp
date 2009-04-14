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

