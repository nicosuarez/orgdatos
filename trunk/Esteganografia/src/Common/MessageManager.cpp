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

MessageManager::MessageManager(): orgMsg(PATH_MESSAGE_FILE, MsgRegistry::Create),
								  orgListImages(PATH_IMG_LIST_FILE, ListImgRegistry::Create),
								  orgNamesMsg(PATH_NAMES_MSG_FILE)
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
	delete instance;

}
/* -------------------------------------------------------------------------- */

Message MessageManager::Extract(Message msg,Message msgTarget){
	Message m1=EncriptationManager::Decrypt(msg);
	CompressionManager::Decompress(m1,msgTarget);
	if( remove( m1.GetFilePath()) != 0 )
		perror( "Error deleting file" );
	return msgTarget;
}
/* -------------------------------------------------------------------------- */

void MessageManager::Hide(Message msg,Message msgTarget){
	Message m1=CompressionManager::Compress(msg);
	ImageManager *imageManager = ImageManager::GetInstance();
	if( imageManager->GetTotalFreeSize() < m1.GetSize() )
	{
		perror( ERR_NOT_SPACE );
		return;
	}
//	list<Space> spaces = imageManager->GetSpacesToStore(m1.GetSize());
//	ID_type idMsg = orgNamesMsg.WriteText(m1.GetName());
//	list<Space>::iterator it = spaces.begin();
//	Space space = dynamic_cast<Space&>(*it);
//
//	ListImgRegistry reg(space->GetInitialPosition(), space.GetSize())
//	orgListImages.CreateList()
//	for(it; it != spaces.end(); it++)
//	{
//		
//		ListImgRegistry reg(space->)
//		orgListImages.AddToListLast()
//	}
	
	EncriptationManager::Encrypt(m1, msgTarget);
	if( remove( m1.GetFilePath()) != 0 )
		perror( "Error deleting file" );
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
