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
}

/* -------------------------------------------------------------------------- */

OrgExtensibleRelative::~OrgExtensibleRelative()
{
  if (file != NULL)
    delete file;
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* OrgExtensibleRelative::GetRegistry(ID_type id)
{
  ExtensibleRelativeRegistry *reg;

  file->Open(ExtensibleRelativeFile::READ);
  reg = file->Read(id);
  file->Close();

  return (reg->IsDeleted() ? NULL : reg);
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::WriteRegistry(ExtensibleRelativeRegistry &reg)
{
  file->Open(ExtensibleRelativeFile::WRITE);
  file->Write(reg);
  file->Close();
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::UpdateRegistry(const ExtensibleRelativeRegistry &reg)
{
  file->Open(ExtensibleRelativeFile::WRITE);
  file->Update(reg);
  file->Close();
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::DeleteRegistry(ID_type id)
{
  file->Open(ExtensibleRelativeFile::WRITE);
  file->Delete(id);
  file->Close();
}

/* -------------------------------------------------------------------------- */

void OrgExtensibleRelative::Destroy()
{
  file->Destroy();
  delete file;
  file = NULL;
}

