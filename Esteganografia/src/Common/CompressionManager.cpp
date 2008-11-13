///////////////////////////////////////////////////////////
//  CompressionManager.cpp
//  Implementation of the Class CompressionManager
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "CompressionManager.h"

CompressionManager* CompressionManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


CompressionManager::CompressionManager(){

}
/* -------------------------------------------------------------------------- */


CompressionManager* CompressionManager::GetInstance()
{
	if(instance == NULL)
		instance = new CompressionManager();
	return instance;
}
/* -------------------------------------------------------------------------- */


CompressionManager::~CompressionManager(){

}
/* -------------------------------------------------------------------------- */


Message CompressionManager::Compress(Message msg){
	return msg;
}
/* -------------------------------------------------------------------------- */


Message CompressionManager::Decompress(Message msg){
	return msg;
}
/* -------------------------------------------------------------------------- */
