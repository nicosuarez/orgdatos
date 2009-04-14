/* -------------------------------------------------------------------------- */
// WikiArticlesParser.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _WIKI_ARTICLES_PARSER_
#define _WIKI_ARTICLES_PARSER_

#include <glibmm/ustring.h>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include "Defines.h"
#include "ArticleParserManager.h"

using Glib::ustring;
using namespace xmlpp;

/* This class parse all the articles of the Wikipedia from its dump. */
class WikiArticlesParser
{
  public:
    /* Constructor. 
     * dumpPath: Path to the dump file. */
    WikiArticlesParser(const ustring &dumpPath);

    /* Destructor. */ 
    virtual ~WikiArticlesParser();

    /* Parse all the articles of the Wikipedia from its dump. */
    void Parse();

	private:
		ustring dumpPath;
		ArticleParserManager parserManager;

		/* Allocation and copy constructor are private to prevent errors. */
    WikiArticlesParser(const WikiArticlesParser &wikiArticlesParser);
    WikiArticlesParser& operator=(const WikiArticlesParser &wikiArticlesParser);
};

#endif

