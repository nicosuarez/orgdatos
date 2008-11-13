#ifndef	__MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <fstream>
#include <iostream>
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

	void SetFilePath(std::string st);

	/*Setea un nuevo id al mensaje*/
	void SetId(unsigned long newId);


private:
	std::string filePath;
	long hiddenSize;
	unsigned long messageID;

};
#endif // __MESSAGE_H__
