///////////////////////////////////////////////////////////
//  Message.h
//  Implementation of the Class Message
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include <string>
using namespace std;
/**
 * Clase que representa el mensaje a ocultar.
 */
class Message
{

public:
	Message();
	virtual ~Message();

	const char* GetFilePath() const;
	long GetSize() const;

private:
	string filePath;
	long size;

};
#endif // !defined(EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_)
