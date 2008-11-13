///////////////////////////////////////////////////////////
//  Message.h
//  Implementation of the Class Message
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include <string>
#include <fstream>
#include <iostream>
using namespace std;
/**
 * Clase que representa el mensaje a ocultar.
 */
class Message
{

public:
	
	/* Constructor */
	Message(string filePath);
	
	/*Destructor*/
	virtual ~Message();
	
	/*Obtiene el path donde almacenar o leer el mensaje */
	const char* GetFilePath() const;
	
	/* Obtiene el tamano total del mensaje */
	long GetSize() const;
	
	/* Obtiene la cantidad en bytes que se ocultaron del mensaje */
	long GetHiddenSize() const;
	
	/*Devuelve el id del mensaje*/
	unsigned long GetId() const;
	
	/* Incrementa la cantidad de bytes ocultos del mensaje en la imagen */
	long IncHiddenSize(long size);
	
	void SetSize(long size);
	
	/* Setea el tamano en bytes ocultos en la imagen */
	void SetHiddenSize(long size);
	
	/*Setea un nuevo id al mensaje*/
	void SetId(unsigned long newId);
	

private:
	string filePath;
	long hiddenSize;
	unsigned long messageID;

};
#endif // !defined(EA_B68DB904_98EA_11dd_B49B_001B2425640C__INCLUDED_)
