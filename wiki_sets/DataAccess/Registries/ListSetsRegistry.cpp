#include "ListSetsRegistry.h"

ListSetsRegistry::ListSetsRegistry()
{
	idInitial = 0;
	idSets = 0;
}

ListSetsRegistry::ListSetsRegistry(ID_type idInitial, ID_type idSets)
{
	this->idInitial = idInitial;
	this->idSets = idSets;
}

ListSetsRegistry::~ListSetsRegistry()
{

}

ExtensibleRelativeRegistry* ListSetsRegistry::Create()
{
	return new ListSetsRegistry();
}

unsigned int ListSetsRegistry::GetSize() const
{
	return (ListRegistry::GetSize() + sizeof(idInitial) + sizeof(idSets));
}

char* ListSetsRegistry::Serialize() const
{
	char* buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	AddToSerialization(buffer, &idInitial, pos, sizeof(idInitial));
	pos += sizeof(idInitial);
	AddToSerialization(buffer, &idSets, pos, sizeof(idSets));
	return buffer;
}

void ListSetsRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	GetFromSerialization(buffer, &idInitial, pos, sizeof(idInitial));
	pos += sizeof(idInitial);
	GetFromSerialization(buffer, &idSets, pos, sizeof(idSets));
}

ID_type ListSetsRegistry::GetIdInitial()const
{
	return idInitial;
}

ID_type ListSetsRegistry::GetIdSets()const
{
	return idSets;
}

void ListSetsRegistry::SetIdInitial(ID_type idInitial)
{
	this->idInitial = idInitial;
}

void ListSetsRegistry::SetIdSets(ID_type idSets)
{
	this->idSets = idSets;
}

std::list<ID_type>* ListSetsRegistry::GetListSets()const
{
	std::list<ID_type>* listSets = new std::list<ID_type>;
	unsigned int totalBits = sizeof(idSets)*8;
	for(unsigned int i=0; i<totalBits; i++)
	{
		if((idSets >> (totalBits-1-i) & 1) == 1)
		{
			listSets->push_back(idInitial + i);
		}
	}
	return listSets;
}

void ListSetsRegistry::AddIdSet(ID_type idSet)
{
	if( (idSet< idInitial) || (idSet > (idInitial + sizeof(idSets)*8 -1)) )
		return;
	unsigned int byte = 1;
	byte = byte <<	(idSet-idInitial);
	idSets = idSets | byte;
}
