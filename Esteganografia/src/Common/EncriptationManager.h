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

	/*Devuelve la unica instancia de EncriptationManager (clase singleton)*/
	static EncriptationManager* GetInstance();

	/* Retorna el mensaje desencriptado con la password */
	Message static Decrypt(string pass, Message msg);
	
	/* Retorna el mensaje encriptado con la password */
	Message static Encrypt(string pass, Message msg);
	
	/* Destructor */
	virtual ~EncriptationManager();

private:
	
	/*Puntero a la unica instancia del EncriptationManager*/
	static EncriptationManager* instance;
	
	/*Constructor privado*/
	EncriptationManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
	EncriptationManager(const EncriptationManager &manager);
	EncriptationManager& operator=(const EncriptationManager &manager);

};
#endif // !defined(EA_B3E47C10_98EA_11dd_B49B_001B2425640C__INCLUDED_)
