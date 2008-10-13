///////////////////////////////////////////////////////////
//  Gif.h
//  Implementation of the Class Gif
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"

/**
 * Gif Formato.
 */
class Gif : public Image
{

public:
	Gif();
	virtual ~Gif();

	void Extract(Space space, Message msg);
	virtual void Hide(Space space, Message msg);

};
#endif // !defined(EA_B491B574_98EA_11dd_B49B_001B2425640C__INCLUDED_)
