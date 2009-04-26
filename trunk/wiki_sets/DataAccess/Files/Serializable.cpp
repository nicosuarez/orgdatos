/* -------------------------------------------------------------------------- */
// Serializable.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "Serializable.h"

Serializable::Serializable()
{
}

/* -------------------------------------------------------------------------- */

Serializable::~Serializable()
{
}

/* -------------------------------------------------------------------------- */

void Serializable::AddToSerialization(char *buffer, const void *item, unsigned int pos, unsigned int length) const
{
  if ((pos + length) > GetSize())
    throw "Index out of range when trying to serialize.";

  buffer += pos;
  memcpy(buffer, item, length);
}

/* -------------------------------------------------------------------------- */

void Serializable::GetFromSerialization(const char *buffer, void *item, unsigned int pos, unsigned int length) const
{
  if ((pos + length) > GetSize())
    throw "Index out of range when trying to deserialize.";

  buffer += pos;
  memcpy(item, buffer, length);
}

