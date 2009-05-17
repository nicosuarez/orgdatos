/* -------------------------------------------------------------------------- */
// ParseResultDump.cpp
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "ParseResultDump.h"

ParseResultDump::ParseResultDump(const ustring &dumpPath)
{
	this->file.open(dumpPath.c_str(), std::ios_base::out);
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
//		WordsManager *wordsManager = WordsManager::getInstance();
//		this->file << std::endl << "=== " << title->raw() << " ===" << std::endl;
		this->file << std::endl << title->raw() << std::endl;
//		result->Add(title);
//		ID_type idSet = SetsManager::getInstance()->addSet();
//		wordsManager->addWord(title->raw(), idSet);
		ParseResult::Iterator it;
		ParseResult::Iterator end = result->End();

		for (it = result->Begin(); it != end; ++it)
		{
			this->file << (*it).raw() << std::endl;
//			wordsManager->addWord((*it).raw(), idSet);

		}

		this->file.flush();
	}
}

