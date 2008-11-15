#ifndef	__MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <fstream>
#include <iostream>
#include "StrToken.h"
/**
 * Clase que representa el mensaje a ocultar.
 */
class Message
{

public:
	/* Constructor */
	Message(std::string filePath);
	Message();

	/*Destructor*/
	virtual ~Message();

	/*Obtiene el path donde almacenar o leer el mensaje */
	const char* GetFilePath() const;

	/* Obtiene el tamano total del mensaje */
	unsigned long GetSize() const;

	/* Obtiene la cantidad en bytes que se ocultaron del mensaje */
	unsigned long GetHiddenSize() const;

	/*Devuelve el id del mensaje*/
	unsigned long GetId() const;
	
	/*Devuelve el nombre del mensaje*/
	std::string GetName() const;

	/* Incrementa la cantidad de bytes ocultos del mensaje en la imagen */
	unsigned long IncHiddenSize(unsigned long size);

	void SetSize(unsigned long size);

	/* Setea el tamano en bytes ocultos en la imagen */
	void SetHiddenSize(unsigned long size);

	/* Setea el archivo donde se encuentra el mensaje */
	void SetFilePath(std::string filePath);

	/*Setea un nuevo id al mensaje*/
	void SetId(unsigned long newId);


private:
	std::string filePath;
	std::string name;
	unsigned long hiddenSize;
	unsigned long messageID;

};
#endif // __MESSAGE_H__
