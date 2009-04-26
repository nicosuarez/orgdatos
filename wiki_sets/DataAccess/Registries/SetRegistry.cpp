#include "SetRegistry.h"

SetRegistry::SetRegistry()
{
	this->offsetListWords = 0;
}

SetRegistry::SetRegistry(ID_type offsetListWords)
{
	this->offsetListWords = offsetListWords;
}

SetRegistry::~SetRegistry()
{
}

ExtensibleRelativeRegistry* SetRegistry::Create()
{
	return new SetRegistry();
}

ID_type SetRegistry::GetOffsetListWords() const
{
	return offsetListWords;
}

void SetRegistry::SetOffsetListWords(ID_type offsetListWords)
{
	this->offsetListWords = offsetListWords;
}

unsigned int SetRegistry::GetSize()const
{
	return (ExtensibleRelativeRegistry::GetSize() + sizeof(offsetListWords));
}

char* SetRegistry::Serialize() const
{
	char *buffer = ExtensibleRelativeRegistry::Serialize();
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	AddToSerialization(buffer, &offsetListWords, pos, sizeof(offsetListWords));
	return buffer;
}

void SetRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ExtensibleRelativeRegistry::Deserialize(buffer, length);
	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
	GetFromSerialization(buffer, &offsetListWords, pos, sizeof(offsetListWords));
}
