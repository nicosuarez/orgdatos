///////////////////////////////////////////////////////////
//  MessageManager.h
//  Implementation of the Class MessageManager
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B6E51C58_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B6E51C58_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Message.h"

/**
 * Clase que maneja el comportamiento de los mensajes, ocultandolos y extrayendolos
 */
class MessageManager
{

public:
	MessageManager();
	virtual ~MessageManager();

	Message Extract(Message msg);
	void Hide(Message msg);

};
#endif // !defined(EA_B6E51C58_98EA_11dd_B49B_001B2425640C__INCLUDED_)
