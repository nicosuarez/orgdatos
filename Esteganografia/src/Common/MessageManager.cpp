///////////////////////////////////////////////////////////
//  MessageManager.cpp
//  Implementation of the Class MessageManager
//  Created on:      13-Oct-2008 2:49:35 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "MessageManager.h"

MessageManager* MessageManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


MessageManager::MessageManager()
{

}
/* -------------------------------------------------------------------------- */


MessageManager* MessageManager::GetInstance()
{
	if(instance == NULL)
		instance = new MessageManager();
	return instance;
}
/* -------------------------------------------------------------------------- */


MessageManager::~MessageManager(){

}
/* -------------------------------------------------------------------------- */


Message MessageManager::Extract(Message msg){
	return msg;
}
/* -------------------------------------------------------------------------- */


void MessageManager::Hide(Message msg){

}
/* -------------------------------------------------------------------------- */


void MessageManager::DeleteMessage(unsigned long messageId)
{
	
}
/* -------------------------------------------------------------------------- */


list<Space> MessageManager::GetFullSpaces(unsigned long messageId)
{
	list<Space> lista;
	return lista;
}
/* -------------------------------------------------------------------------- */
