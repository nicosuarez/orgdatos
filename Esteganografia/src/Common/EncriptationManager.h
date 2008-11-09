///////////////////////////////////////////////////////////
//  EncriptationManager.h
//  Implementation of the Class EncriptationManager
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B3E47C10_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B3E47C10_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Message.h"

/**
 * Clase que se encarga de encriptar y desencriptar el mensaje a ocultar.
 */
class EncriptationManager
{

public:
	EncriptationManager();
	virtual ~EncriptationManager();

	Message static Decrypt(string pass, Message msg);
	Message static Encrypt(string pass, Message msg);

};
#endif // !defined(EA_B3E47C10_98EA_11dd_B49B_001B2425640C__INCLUDED_)
