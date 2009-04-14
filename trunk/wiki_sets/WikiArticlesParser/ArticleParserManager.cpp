/* -------------------------------------------------------------------------- */
// ArticleParserManager.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "ArticleParserManager.h"

ArticleParserManager::ArticleParserManager()
{
	this->Initialize();
}

/* -------------------------------------------------------------------------- */

ArticleParserManager::~ArticleParserManager()
{
	if (this->threads != NULL)
	{
		for (unsigned i = 0; i < ARTICLE_PARSER_MANAGER_MAX_THREADS; ++i)
		{
			ThreadArticleParser *thread = this->threads[i];

			if (thread != NULL)
				delete thread;
		}

		this->threadCount = 0;
		delete[] this->threads;
	}
	
	delete this->dump;
}

/* -------------------------------------------------------------------------- */

void ArticleParserManager::Parse(const ustring *title, const ustring *text)
{
	ThreadArticleParser *thread = this->threads[this->threadCount];

	if (thread != NULL)
		delete thread;

	thread = new ThreadArticleParser(title, text, this->dump);
	thread->Run();

	this->threads[this->threadCount] = thread;
	this->threadCount++;

	if (this->threadCount == ARTICLE_PARSER_MANAGER_MAX_THREADS)
		this->threadCount = 0;
}

/* -------------------------------------------------------------------------- */

void ArticleParserManager::Initialize()
{
	this->dump = new ParseResultDump(PARSE_RESULT_DUMP_PATH);

	this->threadCount = 0;
	this->threads = new ThreadArticleParser*[ARTICLE_PARSER_MANAGER_MAX_THREADS];
	
	for (unsigned i = 0; i < ARTICLE_PARSER_MANAGER_MAX_THREADS; ++i)
		this->threads[i] = NULL;
}

