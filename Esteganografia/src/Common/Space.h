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
	Space(ID_type idSpace, ID_type idImg , string filePath, unsigned long initialPosition, unsigned long size);
	Space(string filePath, string format, unsigned long initialPosition, unsigned long size);
	Space(string filePath, unsigned long initialPosition, unsigned long size);
	Space(ID_type idImg, unsigned long initialPosition, unsigned long size);
	Space(string filePath);
	Space(ID_type idSpace, ID_type idImg);
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
	ID_type GetIDSpace() const;
	void SetIDSpace(ID_type spaceId);

protected:
	string filePath;
	string format;
	unsigned long initialPosition;
	unsigned long size;
	ID_type idImg;
	ID_type idSpace;

};
#endif // !defined(EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_)
