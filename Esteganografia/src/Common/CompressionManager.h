///////////////////////////////////////////////////////////
//  CompressionManager.h
//  Implementation of the Class CompressionManager
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B38D9B20_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B38D9B20_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Message.h"

/**
 * Clase que se encarga de la logica de compresion y descompresion de los mensajes
 * aplicando el algoritmo que corresponda.
 */
class CompressionManager
{

public:
	CompressionManager();
	virtual ~CompressionManager();

	Message static Compress(Message msg);
	Message static Decompress(Message msg);

};
#endif // !defined(EA_B38D9B20_98EA_11dd_B49B_001B2425640C__INCLUDED_)
