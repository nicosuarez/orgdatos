///////////////////////////////////////////////////////////
//  StenographicManager.h
//  Implementation of the Class StenographicManager
//  Created on:      13-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B7E9AE7A_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B7E9AE7A_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Message.h"

/**
 * Clase que se encarga de ocultar la informacion dependiendo del formato de las
 * imagenes.
 */
class StenographicManager
{

public:
	StenographicManager();
	virtual ~StenographicManager();

	Message Hide(Message msg, Space space);

};
#endif // !defined(EA_B7E9AE7A_98EA_11dd_B49B_001B2425640C__INCLUDED_)
