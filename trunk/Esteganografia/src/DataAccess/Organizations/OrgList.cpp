/* -------------------------------------------------------------------------- */
// OrgList.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "OrgList.h"

OrgList::OrgList(const string &fileName, ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)())
{
  file = new ExtensibleRelativeFile(fileName, ptrMethodCreateRegistry);

  if (!file->Exists())
  {
    ListRegistry *reg = dynamic_cast<ListRegistry*>((*ptrMethodCreateRegistry)());
    file->Create(reg->GetSize());
    delete reg;
  }

  file->Open(ExtensibleRelativeFile::READ_WRITE);
}

/* -------------------------------------------------------------------------- */

OrgList::~OrgList()
{
  if (file != NULL)
  {
    file->Close();
    delete file;
  }
}

/* -------------------------------------------------------------------------- */

std::list<ListRegistry*>* OrgList::GetList(ID_type first)
{
  ListRegistry *reg = dynamic_cast<ListRegistry*>(file->Read(first));
  AssertFirstReg(*reg);

  std::list<ListRegistry*> *list = new std::list<ListRegistry*>();
  list->push_back(reg);

  ID_type id = reg->GetNextID();

  while (id != 0)
  {
    reg = dynamic_cast<ListRegistry*>(file->Read(id));
    AssertNotDeleted(*reg);

    list->push_back(reg);
    id = reg->GetNextID();
  }

  if (list->size() == 0)
  {
    FreeList(list);
    return NULL;
  }

  return list;
}

/* -------------------------------------------------------------------------- */

void OrgList::CreateList(ListRegistry &firstReg)
{
  firstReg.SetNextID(0);
  firstReg.SetPreviousID(0);

  file->Write(firstReg);
}

/* -------------------------------------------------------------------------- */

void OrgList::AddToListFirst(ListRegistry &reg, ID_type first)
{
  // Read the 'old' first registry of the list.
  ListRegistry *firstReg = dynamic_cast<ListRegistry*>(file->Read(first));
  AssertFirstReg(*firstReg);

  // Set 'old' first registry ID as the next ID of the new one.
  reg.SetNextID(firstReg->GetID());
  reg.SetPreviousID(0);

  file->Write(reg);

  // Set the new registry ID as the previous ID of the 'old' first registry.
  firstReg->SetPreviousID(reg.GetID());
  file->Update(*firstReg);

  delete firstReg;
}

/* -------------------------------------------------------------------------- */

void OrgList::AddToListLast(ListRegistry &reg, ID_type last)
{
  // Read the 'old' last registry of the list.
  ListRegistry *lastReg = dynamic_cast<ListRegistry*>(file->Read(last));
  AssertLastReg(*lastReg);

  // Set 'old' last registry ID as the previous ID of the new one.
  reg.SetNextID(0);
  reg.SetPreviousID(lastReg->GetID());

  file->Write(reg);

  // Set the new registry ID as the next ID of the 'old' last registry.
  lastReg->SetNextID(reg.GetID());
  file->Update(*lastReg);

  delete lastReg;
}

/* -------------------------------------------------------------------------- */

void OrgList::DeleteList(ID_type first)
{
  ListRegistry *reg = dynamic_cast<ListRegistry*>(file->Read(first));
  AssertFirstReg(*reg);

  ID_type id = reg->GetNextID();
  delete reg;

  while (id != 0)
  {
    reg = dynamic_cast<ListRegistry*>(file->Read(id));
    file->Delete(reg->GetID());

    id = reg->GetNextID();
    delete reg;
  }
}

/* -------------------------------------------------------------------------- */

void OrgList::DeleteFromList(ID_type id)
{
  file->Delete(id);

  // Update the list ID depending on the previous and next registries.
  ListRegistry *reg = dynamic_cast<ListRegistry*>(file->Read(id));

  ID_type idNext = 0;
  ListRegistry *next = NULL;

  ID_type idPrevious = 0;
  ListRegistry *previous = NULL;

  if (reg->GetNextID() != 0)
  {
    next = dynamic_cast<ListRegistry*>(file->Read(reg->GetNextID()));
    idNext = next->GetID();
  }

  if (reg->GetPreviousID() != 0)
  {
    previous = dynamic_cast<ListRegistry*>(file->Read(reg->GetPreviousID()));
    idPrevious = previous->GetID();
  }

  if (next != NULL)
  {
    next->SetPreviousID(idPrevious);
    file->Update(*next);
    delete next;
  }

  if (previous != NULL)
  {
    previous->SetNextID(idNext);
    file->Update(*previous);
    delete previous;
  }
  
  delete reg;
}

/* -------------------------------------------------------------------------- */

void OrgList::Destroy()
{
  file->Destroy();
  delete file;
  file = NULL;
}

/* -------------------------------------------------------------------------- */

void OrgList::FreeList(list<ListRegistry*> *list)
{
  std::list<ListRegistry*>::iterator i;

  for (i = list->begin(); i != list->end(); ++i)
    delete *i;

  delete list;
}

/* -------------------------------------------------------------------------- */

void OrgList::AssertLastReg(const ListRegistry &reg) const
{
  AssertNotDeleted(reg);

  if (reg.GetNextID() != 0)
    throw "The registry is not the last of the list.";
}

/* -------------------------------------------------------------------------- */

void OrgList::AssertFirstReg(const ListRegistry &reg) const
{
  AssertNotDeleted(reg);

  if (reg.GetPreviousID() != 0)
    throw "The registry is not the first of the list.";
}

/* -------------------------------------------------------------------------- */

void OrgList::AssertNotDeleted(const ListRegistry &reg) const
{
  if (reg.IsDeleted())
    throw "The registry is marked as Deleted.";
}

