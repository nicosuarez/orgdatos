/* -------------------------------------------------------------------------- */
// ParseResult.cpp
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "ParseResult.h"

ParseResult::ParseResult()
{
}

/* -------------------------------------------------------------------------- */

ParseResult::~ParseResult()
{
}

/* -------------------------------------------------------------------------- */

void ParseResult::Add(const ustring *result)
{
	this->Add(*result);
}

/* -------------------------------------------------------------------------- */

void ParseResult::Add(const ustring &result)
{
	ThreadLocking locking(this->mutex);
	this->results.insert(result.uppercase());
}

/* -------------------------------------------------------------------------- */

ParseResult::Iterator ParseResult::Begin() const
{
	return this->results.begin();
}

/* -------------------------------------------------------------------------- */

ParseResult::Iterator ParseResult::End() const
{
	return this->results.end();
}

