///////////////////////////////////////////////////////////
//  Message.cpp
//  Implementation of the Class Message
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Message.h"

using namespace std;

Message::Message(string filePath)
{
	this->filePath = filePath;
	this->hiddenSize = 0;
}

Message::Message(){
	this->hiddenSize = 0;
}

Message::~Message(){

}

void Message::SetFilePath(std::string filePath)
{
	this->filePath = filePath;
}

/**
 * Obtiene la cantidad en bytes que se ocultaron del mensaje
 */
long Message::GetHiddenSize() const
{
	return this->hiddenSize;
}

/**
 * Setea el tamano en bytes ocultos en la imagen.
 */
void Message::SetHiddenSize(long size)
{
	this->hiddenSize = size;
}

/**
 * Incrementa la cantidad de bytes ocultos del mensaje en la imagen.
 */
long Message::IncHiddenSize(long size)
{
	this->SetHiddenSize(this->hiddenSize + size);
	return this->hiddenSize;
}

/**
 * Obtiene el path donde almacenar o leer el mensaje.
 */
const char* Message::GetFilePath() const{

	return  this->filePath.c_str();
}

/**
 * Obtiene el tamano total del mensaje
 */
long Message::GetSize() const
{
	long pos = 0;
	ifstream fin(this->filePath.c_str());
	if(fin)
	{
	   fin.seekg(0, ios::end); 
	   pos = fin.tellg();
	}
	fin.close();
	return pos;
}
