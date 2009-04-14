/* -------------------------------------------------------------------------- */
// ArticleParserManager.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _ARTICLE_PARSER_MANAGER_
#define _ARTICLE_PARSER_MANAGER_

#include <glibmm/ustring.h>

#include "Defines.h"
#include "ParseResultDump.h"
#include "ThreadArticleParser.h"

using Glib::ustring;

/* This class manages the parsing of the articles, using one separate thread
 * for each article that needs to be parsed, so more than one article can be
 * parsed at the same time. */
class ArticleParserManager
{
	public:
    /* Constructor. */
    ArticleParserManager();

    /* Destructor. */ 
    virtual ~ArticleParserManager();

		/* Parse the article.
		 * title: Title of the article to parse.
		 * text: Text article to parse. */
		void Parse(const ustring *title, const ustring *text);

	private:
		ParseResultDump *dump;

		unsigned threadCount;
		ThreadArticleParser **threads;

		/* Initialize the class members. */
		void Initialize();
		
		/* Allocation and copy constructor are private to prevent errors. */
    ArticleParserManager(const ArticleParserManager &articleParserManager);
    ArticleParserManager& operator=(const ArticleParserManager &articleParserManager);
};

#endif

