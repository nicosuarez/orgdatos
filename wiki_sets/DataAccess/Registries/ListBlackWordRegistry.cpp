#include "ListBlackWordRegistry.h"

ListBlackWordRegistry::ListBlackWordRegistry()
{
	this->idWord = 0;

}

ListBlackWordRegistry::ListBlackWordRegistry(ID_type idWord)
{
	this->idWord = idWord;

}

ListBlackWordRegistry::~ListBlackWordRegistry()
{

}

ExtensibleRelativeRegistry* ListBlackWordRegistry::Create()
{
	return new ListBlackWordRegistry();
}

unsigned int ListBlackWordRegistry::GetSize() const
{
	return (ListRegistry::GetSize() + sizeof(idWord));
}

char* ListBlackWordRegistry::Serialize() const
{
	char* buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	AddToSerialization(buffer, &idWord, pos, sizeof(idWord));
	return buffer;
}

void ListBlackWordRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	GetFromSerialization(buffer, &idWord, pos, sizeof(idWord));
}

ID_type ListBlackWordRegistry::GetIdWord()const
{
	return idWord;
}

void ListBlackWordRegistry::SetIdWord(ID_type idWord)
{
	this->idWord = idWord;
}
