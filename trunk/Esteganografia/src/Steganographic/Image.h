///////////////////////////////////////////////////////////
//  Image.h
//  Implementation of the Class Image
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "IStenographic.h"

/**
 * Clase que agrupa todos los formatos de imagenes disponibles.
 */
class Image : public IStenographic
{

public:
	Image();
	virtual bool ValidateFormat(Space* space);
	virtual ~Image();
	
	

};
#endif // !defined(EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_)
