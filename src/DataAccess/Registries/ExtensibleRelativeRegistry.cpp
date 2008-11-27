/* -------------------------------------------------------------------------- */
// ExtensibleRelativeRegistry.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "ExtensibleRelativeRegistry.h"

ExtensibleRelativeRegistry::ExtensibleRelativeRegistry() : Serializable()
{
  SetID(0);
  adminFlags = 0;
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry::~ExtensibleRelativeRegistry()
{
}

/* -------------------------------------------------------------------------- */

ID_type ExtensibleRelativeRegistry::GetID() const
{
  return id;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeRegistry::SetID(ID_type id)
{
  this->id = id;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeRegistry::SetDeleted()
{
  if (!IsDeleted())
  {
    adminFlags = adminFlags | DELETED;
  }
}

/* -------------------------------------------------------------------------- */

bool ExtensibleRelativeRegistry::IsDeleted() const
{
  return ((adminFlags & DELETED) == DELETED);
}

/* -------------------------------------------------------------------------- */

unsigned int ExtensibleRelativeRegistry::GetSize() const
{
  return (sizeof(id) + sizeof(adminFlags));
}

/* -------------------------------------------------------------------------- */

char* ExtensibleRelativeRegistry::Serialize() const
{
  char *buffer = new char[GetSize()];

  unsigned int pos = 0;
  AddToSerialization(buffer, &adminFlags, pos, sizeof(adminFlags));

  pos += sizeof(adminFlags);
  AddToSerialization(buffer, &id, pos, sizeof(id));

  return buffer;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeRegistry::Deserialize(const char* buffer, unsigned int length)
{
  if (GetSize() != length)
    throw "The registry size and the serialization length are different.";

  unsigned int pos = 0;
  GetFromSerialization(buffer, &adminFlags, pos, sizeof(adminFlags));

  pos += sizeof(adminFlags);
  GetFromSerialization(buffer, &id, pos, sizeof(id));
}

