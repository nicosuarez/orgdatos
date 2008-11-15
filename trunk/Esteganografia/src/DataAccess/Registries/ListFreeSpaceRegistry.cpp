#include "ListFreeSpaceRegistry.h"

ListFreeSpaceRegistry::ListFreeSpaceRegistry():ListRegistry()
{
}

ListFreeSpaceRegistry::ListFreeSpaceRegistry(unsigned long offsetImage, unsigned long sizeFreeSpace): ListRegistry()
{
	this->offsetImage = offsetImage;
	this->sizeFreeSpace = sizeFreeSpace;
}

ListFreeSpaceRegistry::~ListFreeSpaceRegistry()
{
}


ExtensibleRelativeRegistry* ListFreeSpaceRegistry::Create()
{
	return new ListFreeSpaceRegistry();
}

unsigned long ListFreeSpaceRegistry::GetOffsetImage() const
{
	return offsetImage;
}

unsigned long ListFreeSpaceRegistry::GetSizeFreeSpace() const
{
	return sizeFreeSpace;
}

unsigned int ListFreeSpaceRegistry::GetSize() const
{
	return ( ListRegistry::GetSize() + sizeof(offsetImage) + sizeof(sizeFreeSpace) );
}

void ListFreeSpaceRegistry::SetOffsetImage(unsigned long offsetImage)
{
	this->offsetImage = offsetImage;
}

void ListFreeSpaceRegistry::SetSizeFreeSpace(unsigned long sizeFreeSpace)
{
	this->sizeFreeSpace = sizeFreeSpace;
}

char* ListFreeSpaceRegistry::Serialize() const
{
	char *buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	
	AddToSerialization(buffer, &offsetImage, pos, sizeof(offsetImage));
	pos += sizeof(offsetImage);
	AddToSerialization(buffer, &sizeFreeSpace, pos, sizeof(sizeFreeSpace));
	
	return buffer;
}

void ListFreeSpaceRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	
	GetFromSerialization(buffer, &offsetImage, pos, sizeof(offsetImage));
	pos += sizeof(offsetImage);
	GetFromSerialization(buffer, &sizeFreeSpace, pos, sizeof(sizeFreeSpace));
}
