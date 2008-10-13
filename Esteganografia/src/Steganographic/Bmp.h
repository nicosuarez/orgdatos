///////////////////////////////////////////////////////////
//  Bmp.h
//  Implementation of the Class Bmp
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B2D82F06_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B2D82F06_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"

/**
 * Formato BitMap soporta 16bits,24bits,256 colors.
 * Se utiliza LSB para ocultar la informacion.
 */
class Bmp : public Image
{

public:
	Bmp();
	virtual ~Bmp();

	void Extract(Space space, Message msg);
	virtual void Hide(Space space, Message msg);

};
#endif // !defined(EA_B2D82F06_98EA_11dd_B49B_001B2425640C__INCLUDED_)
