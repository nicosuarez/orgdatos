/* -------------------------------------------------------------------------- */
// ParseResult.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _PARSE_RESULT_
#define _PARSE_RESULT_

#include <set>
#include <glibmm/ustring.h>

#include "ThreadMutex.h"
#include "ThreadLocking.h"

using Glib::ustring;
using namespace std;

/* Container of unique results of the parsing process. */
class ParseResult
{
	public:
		/* Constructor. */
		ParseResult();

		/* Destructor. */
		~ParseResult();

		/* Adds a result into the container. 
		 * result: Result to add. */
		void Add(const ustring *result);
		void Add(const ustring &result);

		/* Type definition of the iterator. */
		typedef set<ustring>::iterator Iterator;

		/* Gets an iterator pointing to the begining of the results. */		
		Iterator Begin() const;

		/* Gets an iterator pointing to the end of the results. */		
		Iterator End() const;

	private:
		ThreadMutex mutex;
		set<ustring> results;

		/* Allocation and copy constructor are private to prevent errors. */
		ParseResult(const ParseResult &parseResult);
		ParseResult& operator=(const ParseResult &parseResult);
};

#endif
