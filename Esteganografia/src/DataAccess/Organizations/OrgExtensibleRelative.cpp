/* -------------------------------------------------------------------------- */
// OrgExtensibleRelative.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "OrgExtensibleRelative.h"

OrgExtensibleRelative::OrgExtensibleRelative(const string &fileName, ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)())
{
  file = new ExtensibleRelativeFile(fileName, ptrMethodCreateRegistry);

  if (!file->Exists())
  {
    ExtensibleRelativeRegistry *reg = (*ptrMethodCreateRegistry)();
    file->Create(reg->GetSize());
    delete reg;
  }

  file->Open(ExtensibleRelativeFile::READ_WRITE);
}

/* -------------------------------------------------------------------------- */

OrgExtensibleRelative::~OrgExtensibleRelative()
{
  if (file != NULL)
  {
    file->Close();
    delete file;
  }
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::SeekRegistry(ID_type id)
{
  file->Seek(id); 
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* OrgExtensibleRelative::GetRegistry(ID_type id)
{
  ExtensibleRelativeRegistry *reg = file->Read(id);

  if (reg->IsDeleted())
  {
    delete reg;
    return NULL;
  }

  return reg;
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* OrgExtensibleRelative::GetNextRegistry()
{
  return file->ReadNext();
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::WriteRegistry(ExtensibleRelativeRegistry &reg)
{
  file->Write(reg);
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::UpdateRegistry(const ExtensibleRelativeRegistry &reg)
{
  file->Update(reg);
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::DeleteRegistry(ID_type id)
{
  file->Delete(id);
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::Destroy()
{
  file->Destroy();
  delete file;
  file = NULL;
}

