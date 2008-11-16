#include "MsgRegistry.h"

MsgRegistry::MsgRegistry(): ExtensibleRelativeRegistry()
{
	this->ptrImgList = 0;
}

MsgRegistry::MsgRegistry(ID_type ptrImgList): ExtensibleRelativeRegistry()
{
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

unsigned int MsgRegistry::GetSize() const
{
	return (ExtensibleRelativeRegistry::GetSize() + sizeof(ptrImgList));
}

char* MsgRegistry::Serialize() const
{
	char *buffer = ExtensibleRelativeRegistry::Serialize();
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	AddToSerialization(buffer, &ptrImgList, pos, sizeof(ptrImgList));
	return buffer;
}

void MsgRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ExtensibleRelativeRegistry::Deserialize(buffer, length);
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	GetFromSerialization(buffer, &ptrImgList, pos, sizeof(ptrImgList));
}
