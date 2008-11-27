/* -------------------------------------------------------------------------- */
// TextRegistry.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "TextRegistry.h"

TextRegistry::TextRegistry()
{
  SetOffset(0);
  SetLength(0);
}

/* -------------------------------------------------------------------------- */

TextRegistry::~TextRegistry()
{
}

/* -------------------------------------------------------------------------- */

unsigned int TextRegistry::GetOffset() const
{
  return offset;
}

/* -------------------------------------------------------------------------- */

void TextRegistry::SetOffset(unsigned int offset)
{
  this->offset = offset;
}

/* -------------------------------------------------------------------------- */

unsigned int TextRegistry::GetLength() const
{
  return length;
}

/* -------------------------------------------------------------------------- */

void TextRegistry::SetLength(unsigned int length)
{
  this->length = length;
}

/* -------------------------------------------------------------------------- */

unsigned int TextRegistry::GetSize() const
{
  return ExtensibleRelativeRegistry::GetSize() + sizeof(offset) + sizeof(length);
}

/* -------------------------------------------------------------------------- */

char* TextRegistry::Serialize() const
{
  char *buffer = ExtensibleRelativeRegistry::Serialize();

  unsigned int pos = ExtensibleRelativeRegistry::GetSize();
  AddToSerialization(buffer, &offset, pos, sizeof(offset));

  pos += sizeof(offset);
  AddToSerialization(buffer, &length, pos, sizeof(length));

  return buffer;
}

/* -------------------------------------------------------------------------- */

void TextRegistry::Deserialize(const char* buffer, unsigned int length)
{
  ExtensibleRelativeRegistry::Deserialize(buffer, length);

  unsigned int pos = ExtensibleRelativeRegistry::GetSize();
  GetFromSerialization(buffer, &offset, pos, sizeof(offset));

  pos += sizeof(offset);
  GetFromSerialization(buffer, &(this->length), pos, sizeof(this->length));
}

