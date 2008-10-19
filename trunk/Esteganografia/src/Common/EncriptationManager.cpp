///////////////////////////////////////////////////////////
//  EncriptationManager.cpp
//  Implementation of the Class EncriptationManager
//  Created on:      13-Oct-2008 2:49:30 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "EncriptationManager.h"


EncriptationManager::EncriptationManager(){

}



EncriptationManager::~EncriptationManager(){

}





/**
 * Retorna el mensaje desencriptado con la password.
 */
Message EncriptationManager::Decrypt(string pass, Message msg){
	return msg;
}


/**
 * Retorna el mensaje encriptado con la password.
 */
Message EncriptationManager::Encrypt(string pass, Message msg){
	return msg;
}
