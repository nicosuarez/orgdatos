/* -------------------------------------------------------------------------- */
// ThreadArticleParser.cpp
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "ThreadArticleParser.h"

ThreadArticleParser::ThreadArticleParser(const ustring *title, const ustring *text, ParseResultDump *dump)
{
	this->Initialize(title, text, NULL, dump, true);
	this->results->Add(this->title);
}

/* -------------------------------------------------------------------------- */

ThreadArticleParser::ThreadArticleParser(const ustring *subText, ParseResult *results)
{
	this->Initialize(NULL, subText, results, NULL, false);
}

/* -------------------------------------------------------------------------- */

ThreadArticleParser::~ThreadArticleParser()
{
	pthread_join(*(this->internalThread), NULL);

	delete this->text;
	delete this->internalThread;

	if (this->title != NULL)
		delete this->title;

	if (this->isMainThread)
		delete this->results;
}

/* -------------------------------------------------------------------------- */

void ThreadArticleParser::Run()
{
	if (!this->IsRunning())
		this->isRunning = !pthread_create(this->internalThread, NULL, StaticRun, this);
}

/* -------------------------------------------------------------------------- */

bool ThreadArticleParser::IsRunning() const
{
	return this->isRunning;
}

/* -------------------------------------------------------------------------- */

void ThreadArticleParser::Initialize(const ustring *title, const ustring *text, ParseResult *results, ParseResultDump *dump, bool isMainThread)
{
	this->text = text;
	this->title = title;
	
	this->isRunning = false;
	this->internalThread = new pthread_t();
	
	this->parseThreads = NULL;
	this->parseThreadsCount = 0;
	this->isMainThread = isMainThread;
	
	this->dump = dump;
	this->results = (results != NULL) ? results : new ParseResult();
}

/* -------------------------------------------------------------------------- */

void ThreadArticleParser::Parse()
{
	ustring::size_type length = this->text->length();
	this->parseThreadsCount = ceil(((double)length) / ARTICLE_PARSER_LENGTH_X_THREAD);

	if (this->parseThreadsCount > 1 && this->isMainThread)
	{
		this->ParseInMultipleThreads(length);
	}
	else
	{
		this->ParseInThisThread();
	}
}
		
/* -------------------------------------------------------------------------- */

void ThreadArticleParser::ParseInThisThread()
{
	ArticleTitlesParser articleTitlesParser;
	articleTitlesParser.Parse(this->text, this->results);
}
		
/* -------------------------------------------------------------------------- */

void ThreadArticleParser::ParseInMultipleThreads(ustring::size_type length)
{
	unsigned count = 0;
	this->InitializeMultipleThreads();

	ustring::size_type iStart = 0;
	ustring::size_type iEnd = ARTICLE_PARSER_LENGTH_X_THREAD;

	while (count < this->parseThreadsCount && iStart < length)
	{
		if (iEnd >= length)
			iEnd = length - 1;

		iEnd = this->text->find(ARTICLE_PARSER_SAFE_SPLIT_CHAR, iEnd);

		if (iEnd == ustring::npos)
			iEnd = length;

		ustring *subText = new ustring(this->text->substr(iStart, (iEnd - iStart)));

		if (!subText->empty())
		{
			ThreadArticleParser *thread = new ThreadArticleParser(subText, this->results);
			thread->Run();

			this->parseThreads[count] = thread;
			count++;
		}

		iStart = iEnd;
		iEnd += ARTICLE_PARSER_LENGTH_X_THREAD;
	}

	this->DeleteMultipleThreads();
}

/* -------------------------------------------------------------------------- */

void ThreadArticleParser::InitializeMultipleThreads()
{
	this->parseThreads = new ThreadArticleParser*[this->parseThreadsCount];

	for (unsigned i = 0; i < this->parseThreadsCount; ++i)
		this->parseThreads[i] = NULL;
}

/* -------------------------------------------------------------------------- */

void ThreadArticleParser::DeleteMultipleThreads()
{
	if (this->parseThreads != NULL)
	{
		for (unsigned i = 0; i < this->parseThreadsCount; ++i)
		{
			ThreadArticleParser *thread = this->parseThreads[i];

			if (thread != NULL)
					delete thread;
		}

		this->parseThreadsCount = 0;
		delete[] this->parseThreads;
	}
}
		
/* -------------------------------------------------------------------------- */

void* ThreadArticleParser::StaticRun(void* arg)
{
	ThreadArticleParser* thread = (ThreadArticleParser*)arg;

	thread->Parse();
	
	if (thread->isMainThread)
		thread->dump->Write(thread->title, thread->results);
	
	thread->isRunning = false;

	return NULL;
}
