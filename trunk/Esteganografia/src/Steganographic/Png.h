///////////////////////////////////////////////////////////
//  Png.h
//  Implementation of the Class Png
//  Created on:      13-Oct-2008 2:49:35 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B73EE7E2_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B73EE7E2_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"

/**
 * Formato PNG
 */
class Png : public Image
{

public:
	Png();
	virtual ~Png();

	void Extract(Space space, Message msg);
	virtual void Hide(Space space, Message msg);

};
#endif // !defined(EA_B73EE7E2_98EA_11dd_B49B_001B2425640C__INCLUDED_)
