#include "ListMsgRegistry.h"

ListMsgRegistry::ListMsgRegistry():ListRegistry()
{
}

ListMsgRegistry::ListMsgRegistry( ID_type idImage):ListRegistry()
{
	this->idImage = idImage;
}

ListMsgRegistry::~ListMsgRegistry()
{
}

ID_type ListMsgRegistry::GetIDImage() const
{
	return idImage;
}

unsigned int ListMsgRegistry::GetSize() const
{
	return ( ListRegistry::GetSize() + sizeof(idImage) ); 
}

void ListMsgRegistry::SetIDImage(ID_type idImage)
{
	this->idImage = idImage;
}

char* ListMsgRegistry::Serialize() const
{
	char *buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	AddToSerialization(buffer, &idImage, pos, sizeof(idImage));
	return buffer;
}

void ListMsgRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	GetFromSerialization(buffer, &idImage, pos, sizeof(idImage));	
}
