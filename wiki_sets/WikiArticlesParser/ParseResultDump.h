/* -------------------------------------------------------------------------- */
// ParseResultDump.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _PARSE_RESULT_DUMP_
#define _PARSE_RESULT_DUMP_

#include <fstream>
#include <glibmm/ustring.h>

#include "ParseResult.h"
#include "ThreadMutex.h"
#include "ThreadLocking.h"

using Glib::ustring;

/* Writes the results of the pase of an article in a file. */
class ParseResultDump
{
	public:
    /* Constructor. */
    ParseResultDump(const ustring &dumpPath);

    /* Destructor. */ 
    virtual ~ParseResultDump();

		/* Writes the result of the parse.
		 * title: Title of the article.
		 * result: Result to write. */
		void Write(const ustring *title, const ParseResult *result);

	private:
		fstream file;
		ThreadMutex mutex;

		/* Allocation and copy constructor are private to prevent errors. */
    ParseResultDump(const ParseResultDump &parseResultDump);
    ParseResultDump& operator=(const ParseResultDump &parseResultDump);
};

#endif

