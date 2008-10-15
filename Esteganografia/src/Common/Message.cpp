///////////////////////////////////////////////////////////
//  Message.cpp
//  Implementation of the Class Message
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Message.h"


Message::Message(){

}



Message::~Message(){

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
long Message::GetSize() const{

	return this->size;
}
