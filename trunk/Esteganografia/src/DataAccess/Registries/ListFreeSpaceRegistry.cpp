#include "ListFreeSpaceRegistry.h"

ListFreeSpaceRegistry::ListFreeSpaceRegistry():ListRegistry()
{
	this->idImage = 0;
}

ListFreeSpaceRegistry:: ListFreeSpaceRegistry( ID_type idImage) : ListRegistry()
{
	this->idImage = idImage;
}

ListFreeSpaceRegistry::~ListFreeSpaceRegistry()
{
}

ExtensibleRelativeRegistry* ListFreeSpaceRegistry::Create()
{
	return new ListFreeSpaceRegistry();
}

ID_type ListFreeSpaceRegistry::GetIdImage() const
{
	return idImage;
}

void ListFreeSpaceRegistry::SetIdImage(ID_type idImage)
{
	this->idImage = idImage;
}

unsigned int ListFreeSpaceRegistry::GetSize() const
{
	return (ListRegistry::GetSize() + sizeof(idImage));
}

char* ListFreeSpaceRegistry::Serialize() const
{
	char *buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	
	AddToSerialization(buffer, &idImage, pos, sizeof(idImage));
	pos += sizeof(idImage);
	
	return buffer;
}

void ListFreeSpaceRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	
	GetFromSerialization(buffer, &idImage, pos, sizeof(idImage));
	pos += sizeof(idImage);
	
}

