/* -------------------------------------------------------------------------- */
// ParseResultDump.cpp
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "ParseResultDump.h"

ParseResultDump::ParseResultDump(const ustring &dumpPath)
{
	this->file.open(dumpPath.c_str(), std::ios_base::out);
	this->wordsManager = WordsManager::getInstance();
	this->setsManager = SetsManager::getInstance();
}

/* -------------------------------------------------------------------------- */

ParseResultDump::~ParseResultDump()
{
	this->file.close();
}

/* -------------------------------------------------------------------------- */

//void ParseResultDump::Write(const ustring *title, const ParseResult *result)
void ParseResultDump::Write(const ustring *title, ParseResult *result)
{
	ThreadLocking locking(this->mutex);

	if (this->file.is_open())
	{
		this->file << std::endl << "=== " << title->raw() << " ===" << std::endl;
		result->Add(title);
		ID_type idSet = setsManager->addSet();
		this->wordsManager->addWord(title->raw(), idSet);
		ParseResult::Iterator it;
		ParseResult::Iterator end = result->End();

		for (it = result->Begin(); it != end; ++it)
		{
			this->file << (*it).raw() << std::endl;
			this->wordsManager->addWord((*it).raw(), idSet);

		}

		this->file.flush();
	}
}

