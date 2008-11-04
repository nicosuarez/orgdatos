/* -------------------------------------------------------------------------- */
// ListRegistry.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "ListRegistry.h"

ListRegistry::ListRegistry()
{
  SetNextID(0);
}

/* -------------------------------------------------------------------------- */

ListRegistry::~ListRegistry()
{
}

/* -------------------------------------------------------------------------- */

ID_type ListRegistry::GetNextID() const
{
  return nextId;
}

/* -------------------------------------------------------------------------- */

void ListRegistry::SetNextID(ID_type id)
{
  this->nextId = nextId;
}

/* -------------------------------------------------------------------------- */

unsigned int ListRegistry::GetSize() const
{
  return ExtensibleRelativeRegistry::GetSize() + sizeof(nextId);
}

/* -------------------------------------------------------------------------- */

char* ListRegistry::Serialize() const
{
  char *buffer = ExtensibleRelativeRegistry::Serialize();

  unsigned int pos = ExtensibleRelativeRegistry::GetSize();
  AddToSerialization(buffer, &nextId, pos, sizeof(nextId));

  return buffer;
}

/* -------------------------------------------------------------------------- */

void ListRegistry::Deserialize(const char* buffer, unsigned int length)
{
  ExtensibleRelativeRegistry::Deserialize(buffer, length);

  unsigned int pos = ExtensibleRelativeRegistry::GetSize();
  GetFromSerialization(buffer, &nextId, pos, sizeof(nextId));
}

