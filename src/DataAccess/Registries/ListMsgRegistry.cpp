#include "ListMsgRegistry.h"

ListMsgRegistry::ListMsgRegistry():ListRegistry()
{
}

ListMsgRegistry::ListMsgRegistry( ID_type idMsg):ListRegistry()
{
	this->idMsg = idMsg;
}

ListMsgRegistry::~ListMsgRegistry()
{
}

ExtensibleRelativeRegistry* ListMsgRegistry::Create()
{
	return new ListMsgRegistry();
}

ID_type ListMsgRegistry::GetIDMessage() const
{
	return idMsg;
}

unsigned int ListMsgRegistry::GetSize() const
{
	return ( ListRegistry::GetSize() + sizeof(idMsg) ); 
}

void ListMsgRegistry::SetIDMessage(ID_type idMsg)
{
	this->idMsg = idMsg;
}

char* ListMsgRegistry::Serialize() const
{
	char *buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	AddToSerialization(buffer, &idMsg, pos, sizeof(idMsg));
	return buffer;
}

void ListMsgRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	GetFromSerialization(buffer, &idMsg, pos, sizeof(idMsg));	
}
