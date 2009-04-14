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

void ParseResultDump::Write(const ustring *title, const ParseResult *result)
{
	ThreadLocking locking(this->mutex);

	if (this->file.is_open())
	{
		this->file << std::endl << "=== " << title->raw() << " ===" << std::endl;

		ParseResult::Iterator it;
		ParseResult::Iterator end = result->End();
		
		for (it = result->Begin(); it != end; ++it)
			this->file << (*it).raw() << std::endl;

		this->file.flush();
	}
}

