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
	
	/*Devuelve la unica instancia de CompressionManager (clase singleton)*/
	static CompressionManager* GetInstance();

	/* Comprime el mensaje */
	Message static Compress(Message msg);

	/* Descomprime el mensaje */
	Message static Decompress(Message msg);
	
	/* Destructor */
	virtual ~CompressionManager();
	
private:
	
	/*Puntero a la unica instancia del CompressionManager*/
	static CompressionManager* instance;
	
	/* Constructor privado */
	CompressionManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
	CompressionManager(const CompressionManager &manager);
	CompressionManager& operator=(const CompressionManager &manager);

};
#endif // !defined(EA_B38D9B20_98EA_11dd_B49B_001B2425640C__INCLUDED_)
