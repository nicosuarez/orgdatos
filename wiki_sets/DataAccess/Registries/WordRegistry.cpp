#include "WordRegistry.h"

WordRegistry::WordRegistry()
{
	this->idListSets = 0;
}

WordRegistry::WordRegistry(ID_type idListSets)
{
	this->idListSets = idListSets;
}

WordRegistry::~WordRegistry()
{
}

ExtensibleRelativeRegistry* WordRegistry::Create()
{
	return new WordRegistry();
}

ID_type WordRegistry::GetIdListSets() const
{
	return idListSets;
}

void WordRegistry::SetIdListSets(ID_type idListSets)
{
	this->idListSets = idListSets;
}

unsigned int WordRegistry::GetSize()const
{
	return (ExtensibleRelativeRegistry::GetSize() + sizeof(idListSets));
}

char* WordRegistry::Serialize() const
{
	char *buffer = ExtensibleRelativeRegistry::Serialize();
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	AddToSerialization(buffer, &idListSets, pos, sizeof(idListSets));
	return buffer;
}

void WordRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ExtensibleRelativeRegistry::Deserialize(buffer, length);
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	GetFromSerialization(buffer, &idListSets, pos, sizeof(idListSets));
}
