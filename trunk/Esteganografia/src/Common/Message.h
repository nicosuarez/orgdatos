///////////////////////////////////////////////////////////
//  Message.h
//  Implementation of the Class Message
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include <string>
#include <fstream>
#include <iostream>
using namespace std;
/**
 * Clase que representa el mensaje a ocultar.
 */
class Message
{

public:
	Message(string filePath);
	virtual ~Message();

	const char* GetFilePath() const;
	long GetSize() const;
	long GetHiddenSize() const;
	long IncHiddenSize(long size);
	void SetSize(long size);
	void SetHiddenSize(long size);
	

private:
	string filePath;
	long hiddenSize;

};
#endif // !defined(EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_)
