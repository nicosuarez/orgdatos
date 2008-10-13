///////////////////////////////////////////////////////////
//  ImageFactory.h
//  Implementation of the Class ImageFactory
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B53A0FA8_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B53A0FA8_98EA_11dd_B49B_001B2425640C__INCLUDED_
#include "Image.h"
/**
 * Dado un espacio crea una imagen segun el formato que tenga el espacio.
 */
class ImageFactory
{

public:
	ImageFactory();
	virtual ~ImageFactory();

	Image GetImage(Space space);

};
#endif // !defined(EA_B53A0FA8_98EA_11dd_B49B_001B2425640C__INCLUDED_)
