#include "MsgRegistry.h"

MsgRegistry::MsgRegistry(): ExtensibleRelativeRegistry()
{
	this->idName = 0;
	this->ptrImgList = 0;
}

MsgRegistry::MsgRegistry(ID_type idName, ID_type ptrImgList): ExtensibleRelativeRegistry()
{
	this->idName = idName;
	this->ptrImgList = ptrImgList;
}

MsgRegistry::~MsgRegistry()
{
}


ExtensibleRelativeRegistry* MsgRegistry::Create()
{
	return new MsgRegistry(); 
}

ID_type MsgRegistry::GetPtrImgList() const
{
	return ptrImgList;
}

void MsgRegistry::SetPtrImgList(ID_type ptrImgList)
{
	this->ptrImgList = ptrImgList;
}

ID_type MsgRegistry::GetIdName() const
{
	return idName;
}

void MsgRegistry::SetIdName(ID_type idName)
{
	this->idName = idName;
}

unsigned int MsgRegistry::GetSize() const
{
	return (ExtensibleRelativeRegistry::GetSize() + sizeof(idName) + sizeof(ptrImgList));
}

char* MsgRegistry::Serialize() const
{
	char *buffer = ExtensibleRelativeRegistry::Serialize();
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	AddToSerialization(buffer, &idName, pos, sizeof(idName));
	pos += sizeof(idName);
	AddToSerialization(buffer, &ptrImgList, pos, sizeof(ptrImgList));	
	return buffer;
}

void MsgRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ExtensibleRelativeRegistry::Deserialize(buffer, length);
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	GetFromSerialization(buffer, &idName, pos, sizeof(idName));
	pos += sizeof(idName);
	GetFromSerialization(buffer, &ptrImgList, pos, sizeof(ptrImgList));
}
