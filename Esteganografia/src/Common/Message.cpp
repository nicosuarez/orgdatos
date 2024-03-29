///////////////////////////////////////////////////////////
//  Message.cpp
//  Implementation of the Class Message
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Message.h"

Message::Message(string filePath)
{
	this->filePath = filePath;
	this->hiddenSize = 0;
	this->messageID = 0;
}

Message::Message(const Message &message)
{
	this->filePath = message.GetFilePath();
	this->hiddenSize = message.GetHiddenSize();
	this->messageID = message.GetId();
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
unsigned long Message::GetHiddenSize() const
{
	return this->hiddenSize;
}

/**
 * Setea el tamano en bytes ocultos en la imagen.
 */
void Message::SetHiddenSize(unsigned long size)
{
	this->hiddenSize = size;
}

/**
 * Incrementa la cantidad de bytes ocultos del mensaje en la imagen.
 */
unsigned long Message::IncHiddenSize(unsigned long size)
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

const char* Message::GetName() const
{
	tVecStr tokens = StrToken::getStrTokens(std::string(filePath), "/");
	return ((std::string)tokens.back()).c_str();
}

/**
 * Obtiene el tamano total del mensaje
 */
unsigned long Message::GetSize() const
{
	long pos = 0;
	std::ifstream fin(this->filePath.c_str());
	if(fin)
	{
	   fin.seekg(0, std::ios::end);
	   pos = fin.tellg();
	}
	fin.close();
	return pos;
}

unsigned long Message:: GetId() const
{
	return this->messageID;
}

void Message::Delete(){
	if( remove( filePath.c_str()) != 0 )
		perror( "Error deleting file" );
}
