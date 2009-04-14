/* -------------------------------------------------------------------------- */
// ThreadArticleParser.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _ARTICLE_PARSER_THREAD_
#define _ARTICLE_PARSER_THREAD_

#include <cmath>
#include <pthread.h>
#include <glibmm/ustring.h>

#include "Defines.h"
#include "ParseResult.h"
#include "ParseResultDump.h"
#include "ArticleTitlesParser.h"

using Glib::ustring;

/* Thread that has the responsability to parse the article, in this thread
 * or in multiple sub threads according to the article size. */
class ThreadArticleParser
{
	public:
		/* Constructor.
		 * title: Title of the article to parse.
		 * text: Text article to parse.
		 * dump: Dump where the parse result is written. */
		ThreadArticleParser(const ustring *title, const ustring *text, ParseResultDump *dump);

		/* Destructor. */
		virtual ~ThreadArticleParser();

		/* Starts the thread to parse the article. */
		void Run();

		/* Checks if the thread is running or not. */
		bool IsRunning() const;

	private:
		ParseResult *results;
		ParseResultDump *dump;

		const ustring *text;
		const ustring *title;

		/* Internal thread. */
		bool isRunning;
		pthread_t *internalThread;

		/* Multiple threading option for parsing. */
		bool isMainThread;
		unsigned parseThreadsCount;
		ThreadArticleParser **parseThreads;

		/* Private constructor used in multiple threading.
		 * subText: Part of the text of the article to parse.
		 * results: Set of results to add the new identified results. */
		ThreadArticleParser(const ustring *subText, ParseResult *results);
		
		/* Initialize the class members.
		 * title: Title of the article to parse.
		 * text: Text article to parse.
		 * results: Set of results to add the new identified results.
		 * dump: Dump where the parse result is written.
		 * isMainThread: Is or not the main thread. */
		void Initialize(const ustring *title, const ustring *text, ParseResult *results, ParseResultDump *dump, bool isMainThread);

		/* Parse the article. */
		void Parse();

		/* Parse the article in this thread. Used by Parse method. */
		void ParseInThisThread();

		/* Parse the article in parts in separate threads, according to the 
		 * value of the parseThreadsCount member. Used by Parse method.
		 * length: Length of the text of the article to parse. */
		void ParseInMultipleThreads(ustring::size_type length);

		/* Initialize the multiple threads for parsing. */
		void InitializeMultipleThreads();

		/* Deletes the multiple threads used for parsing. */
		void DeleteMultipleThreads();

		/* Static method that is really executed by the thread. 
		 * arg: It always takes 'this' pointer as parameter. */
		static void* StaticRun(void* arg);

		/* Allocation and copy constructor are private to prevent errors. */
		ThreadArticleParser(const ThreadArticleParser& threadArticleParser);
		ThreadArticleParser& operator=(const ThreadArticleParser& threadArticleParser);
};

#endif
