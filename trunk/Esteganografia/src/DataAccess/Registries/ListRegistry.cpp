/* -------------------------------------------------------------------------- */
// ListRegistry.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "ListRegistry.h"

ListRegistry::ListRegistry()
{
  SetNextID(0);
  SetPreviousID(0);
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
  this->nextId = id;
}

/* -------------------------------------------------------------------------- */

ID_type ListRegistry::GetPreviousID() const
{
  return previousId;
}

/* -------------------------------------------------------------------------- */

void ListRegistry::SetPreviousID(ID_type id)
{
  this->previousId = id;
}

/* -------------------------------------------------------------------------- */

unsigned int ListRegistry::GetSize() const
{
  return ExtensibleRelativeRegistry::GetSize() + sizeof(nextId) + sizeof(previousId);
}

/* -------------------------------------------------------------------------- */

char* ListRegistry::Serialize() const
{
  char *buffer = ExtensibleRelativeRegistry::Serialize();

  unsigned int pos = ExtensibleRelativeRegistry::GetSize();
  AddToSerialization(buffer, &nextId, pos, sizeof(nextId));

  pos += sizeof(nextId);
  AddToSerialization(buffer, &previousId, pos, sizeof(previousId));

  return buffer;
}

/* -------------------------------------------------------------------------- */

void ListRegistry::Deserialize(const char* buffer, unsigned int length)
{
  ExtensibleRelativeRegistry::Deserialize(buffer, length);

  unsigned int pos = ExtensibleRelativeRegistry::GetSize();
  GetFromSerialization(buffer, &nextId, pos, sizeof(nextId));

  pos += sizeof(nextId);
  GetFromSerialization(buffer, &previousId, pos, sizeof(previousId));
}

