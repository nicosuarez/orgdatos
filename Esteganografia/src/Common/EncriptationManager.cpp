///////////////////////////////////////////////////////////
//  EncriptationManager.cpp
//  Implementation of the Class EncriptationManager
//  Created on:      13-Oct-2008 2:49:30 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "EncriptationManager.h"

EncriptationManager* EncriptationManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


EncriptationManager::EncriptationManager(){

}
/* -------------------------------------------------------------------------- */


EncriptationManager* EncriptationManager::GetInstance()
{
	if(instance == NULL)
		instance = new EncriptationManager();
	return instance;
}
/* -------------------------------------------------------------------------- */


EncriptationManager::~EncriptationManager(){

}
/* -------------------------------------------------------------------------- */


Message EncriptationManager::Decrypt(string pass, Message msg){
	return msg;
}
/* -------------------------------------------------------------------------- */


Message EncriptationManager::Encrypt(string pass, Message msg){
	return msg;
}
/* -------------------------------------------------------------------------- */
