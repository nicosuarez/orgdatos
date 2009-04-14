/* -------------------------------------------------------------------------- */
// ArticleTitlesParser.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _ARTICLE_TITLES_PARSER_
#define _ARTICLE_TITLES_PARSER_

#include <glibmm/ustring.h>

#include "Defines.h"
#include "ParseResult.h"

using Glib::ustring;

/* This class parse all the articles title from an article of the 
 * Wikipedia, knowing the possible relations to other articles. */
class ArticleTitlesParser
{
  public:
    /* Constructor. */
    ArticleTitlesParser();

    /* Destructor. */ 
    virtual ~ArticleTitlesParser();

		/* Parse all the articles title from an article of the 
		 * Wikipedia, knowing the possible relations to other articles.
		 * text: Text to parse of the article. 
		 * results: Set of results to add the new identified results. */
		void Parse(const ustring *text, ParseResult *results);

	private:
		/* Gets the article title from the link. 
		 * link: Link to take the article title from. */
		ustring GetArticleTitle(const ustring &link) const;

		/* Checks if the link is a valid article link. 
		 * link: Link to check. */
		bool IsArticleTitleLink(const ustring &link) const;

		/* Allocation and copy constructor are private to prevent errors. */
    ArticleTitlesParser(const ArticleTitlesParser &articleTitlesParser);
    ArticleTitlesParser& operator=(const ArticleTitlesParser &articleTitlesParser);
};

#endif

