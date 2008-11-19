///////////////////////////////////////////////////////////
//  Space.h
//  Implementation of the Class Space
//  Created on:      13-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_
#include <string>
#include <fstream>
#include <iostream>
#include "Resource.h"
using namespace std;
/**
 * Unidad de espacio del cual se puede recuperar o almacenar infomacion.
 */
class Space
{

public:
	Space(string filePath, string format, unsigned long initialPosition, unsigned long size);
	Space(string filePath, unsigned long initialPosition, unsigned long size);
	Space(ID_type idImg, unsigned long initialPosition, unsigned long size);
	Space(string filePath);
	virtual ~Space();

	const char* GetFilePath() const;
	string GetFormat() const;
	unsigned long GetInitialPosition() const;
	unsigned long GetSize() const;
	unsigned long GetTotalSize() const;
	void SetSize(unsigned long size);
	void SetInitialPosition(unsigned long position);
	ID_type GetIDImage() const;
	void SetIDImage(ID_type idImg);

private:
	string filePath;
	string format;
	unsigned long initialPosition;
	unsigned long size;
	ID_type idImg;

};
#endif // !defined(EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_)
