///////////////////////////////////////////////////////////
//  Jpg.h
//  Implementation of the Class Jpg
//  Created on:      13-Oct-2008 2:49:33 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B637FB36_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B637FB36_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"
#include "../Common/CImg.h"

#define JpgFileType "JFIF"

/**
 * Formato comprimido jpg,jpge
 */
class Jpg : public Image
{

public:
	Jpg();
	Jpg(const char* filePath);
	virtual ~Jpg();

	static bool ValidateFormat(Space* space);
	virtual void Extract(Space* space, Message* msg);
	virtual void Hide(Space* space, Message* msg);
	bool Load();

};
#endif // !defined(EA_B637FB36_98EA_11dd_B49B_001B2425640C__INCLUDED_)
