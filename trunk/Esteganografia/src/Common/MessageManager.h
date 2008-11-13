///////////////////////////////////////////////////////////
//  MessageManager.h
//  Implementation of the Class MessageManager
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B6E51C58_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B6E51C58_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Message.h"
#include "Space.h"
#include <list>

/**
 * Clase que maneja el comportamiento de los mensajes, ocultandolos y extrayendolos
 */
class MessageManager
{

public:
	
	/*Devuelve la unica instancia de MessageManager (clase singleton)*/
	static MessageManager* GetInstance();
		
	/*Extrae el mensaje oculto y lo devuelve como un nuevo mensaje*/
	Message Extract(Message msg);
	
	/*Oculta un mensaje*/
	void Hide(Message msg);
	
	/*Elimina un mensaje oculto*/
	void DeleteMessage(unsigned long messageId);
	
	/*Devuelve una lista con los distintos espacios en los 
	 * cuales el mensaje esta oculto */
	list<Space> GetFullSpaces(unsigned long messageId);
	
	/*Destructor*/
	virtual ~MessageManager();

private:
	
	/*Puntero a la unica instancia del MessageManager*/
	static MessageManager* instance;
	
	/*Constructor privado*/
	MessageManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
    MessageManager(const MessageManager &manager);
    MessageManager& operator=(const MessageManager &manager);

};
#endif // !defined(EA_B6E51C58_98EA_11dd_B49B_001B2425640C__INCLUDED_)
