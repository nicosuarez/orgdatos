#include "ListFreeSpaceRegistry.h"

ListFreeSpaceRegistry::ListFreeSpaceRegistry():ListRegistry()
{
	this->idImage = 0;
	this->size = 0;
}

ListFreeSpaceRegistry:: ListFreeSpaceRegistry(ID_type idImage) : ListRegistry()
{
	this->idImage = idImage;
	this->size = 0;
}

ListFreeSpaceRegistry:: ListFreeSpaceRegistry(ID_type idImage, unsigned long size) : ListRegistry()
{
	this->idImage = idImage;
	this->size = size;
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
	return (ListRegistry::GetSize() + sizeof(idImage) + sizeof(size));
}

unsigned long ListFreeSpaceRegistry::GetSpaceSize() const
{
	return this->size;
}

void ListFreeSpaceRegistry::SetSpaceSize(unsigned long size)
{
	this->size = size;
}

char* ListFreeSpaceRegistry::Serialize() const
{
	char *buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	
	AddToSerialization(buffer, &idImage, pos, sizeof(idImage));
	pos += sizeof(idImage);
	AddToSerialization(buffer, &size, pos, sizeof(size));
	pos += sizeof(size);
	
	return buffer;
}

void ListFreeSpaceRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	
	GetFromSerialization(buffer, &idImage, pos, sizeof(idImage));
	pos += sizeof(idImage);
	GetFromSerialization(buffer, &size, pos, sizeof(size));
	pos += sizeof(size);
	
}

