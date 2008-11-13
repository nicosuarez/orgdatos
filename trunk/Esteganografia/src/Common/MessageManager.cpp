///////////////////////////////////////////////////////////
//  MessageManager.cpp
//  Implementation of the Class MessageManager
//  Created on:      13-Oct-2008 2:49:35 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "MessageManager.h"
#include "EncriptationManager.h"
#include "CompressionManager.h"
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
	Message m1=EncriptationManager::Decrypt(msg);
	Message ans=CompressionManager::Decompress(m1);
	if( remove( m1.GetFilePath()) != 0 )
		perror( "Error deleting file" );
	return ans;
}
/* -------------------------------------------------------------------------- */

Message MessageManager::Hide(Message msg){
	Message m1=CompressionManager::Compress(msg);
	Message ans=EncriptationManager::Encrypt(m1);
	if( remove( m1.GetFilePath()) != 0 )
		perror( "Error deleting file" );
	return ans;
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
