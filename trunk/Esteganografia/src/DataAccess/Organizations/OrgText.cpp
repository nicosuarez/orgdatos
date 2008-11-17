/* -------------------------------------------------------------------------- */
// OrgText.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "OrgText.h"

OrgText::OrgText(const string &path,const string &fileName)
{
  string activeFileName = ("a_" + fileName);
  activeFileName=path + activeFileName;
  orgActive = new OrgExtensibleRelative(activeFileName, CreateTextRegistry);

  string deletedFileName = ("d_" + fileName);
  deletedFileName=path+deletedFileName;
  orgDeleted = new OrgExtensibleRelative(deletedFileName, CreateTextRegistry);

  OpenStream(fileName);
}

/* -------------------------------------------------------------------------- */

OrgText::~OrgText()
{
  if (orgActive != NULL)
    delete orgActive;

  if (orgDeleted != NULL)
    delete orgDeleted;

  if (fileName != NULL)
    delete fileName;

  stream.close();
}

/* -------------------------------------------------------------------------- */

string OrgText::GetText(ID_type id)
{
  AssertStreamOpened();

  TextRegistry *reg = dynamic_cast<TextRegistry*>(orgActive->GetRegistry(id));
  AssertNotDeleted(*reg);

  unsigned int size = reg->GetLength() + 1;
  unsigned char *c_text = new unsigned char[size];
  memset(c_text, '\0', size);

  stream.seekg(reg->GetOffset(), ios_base::beg);
  stream.read((char*)c_text, reg->GetLength());

  string text((char*)c_text);

  delete reg;
  delete[] c_text;

  return text;
}

/* -------------------------------------------------------------------------- */

ID_type OrgText::WriteText(const string &text)
{
  AssertStreamOpened();

  unsigned int offset = InternalWriteText(text);

  // Write the registry that reference the text.
  TextRegistry *reg = new TextRegistry();

  reg->SetOffset(offset);
  reg->SetLength(text.length());

  orgActive->WriteRegistry(*reg);

  ID_type id = reg->GetID();
  delete reg;

  return id;
}

/* -------------------------------------------------------------------------- */

void OrgText::UpdateText(ID_type id, const string &text)
{
  AssertStreamOpened();

  TextRegistry *reg = dynamic_cast<TextRegistry*>(orgActive->GetRegistry(id));
  AssertNotDeleted(*reg);

  // Same length, no problem, just update the text.
  if (text.length() == reg->GetLength())
  {
    stream.seekg(reg->GetOffset(), ios_base::beg);
    stream.write(text.c_str(), text.length());
    stream.flush();
  }
  else
  {
    // New text length is minor.
    if (text.length() < reg->GetLength())
    {
      // Add new deleted space.
      unsigned int length = reg->GetLength() - text.length();
      unsigned int offset = reg->GetOffset() + text.length();
      InternalDeleteText(NULL, offset, length);  

      // Update at the same offset.
      stream.seekg(reg->GetOffset(), ios_base::beg);
      stream.write(text.c_str(), text.length());
      stream.flush();
    }
    // New text length is larger.
    else
    {
      // Delete the current offset and length.
      InternalDeleteText(NULL, reg->GetOffset(), reg->GetLength());

      // Write the text again like a new one.
      unsigned int offset = InternalWriteText(text);
      reg->SetOffset(offset);
    }

    // Update the registry.
    reg->SetLength(text.length());
    orgActive->UpdateRegistry(*reg);
  }
  
  delete reg;
}

/* -------------------------------------------------------------------------- */

void OrgText::DeleteText(ID_type id)
{
  TextRegistry *active = dynamic_cast<TextRegistry*>(orgActive->GetRegistry(id));

  InternalDeleteText(NULL, active->GetOffset(), active->GetLength());
  orgActive->DeleteRegistry(id);

  delete active;
}

/* -------------------------------------------------------------------------- */

void OrgText::Destroy()
{
  orgActive->Destroy();
  delete orgActive;
  orgActive = NULL;

  orgDeleted->Destroy();
  delete orgDeleted;
  orgDeleted = NULL;

  stream.close();
  remove((*fileName).c_str());

  delete fileName;
  fileName = NULL;
}

/* -------------------------------------------------------------------------- */

void OrgText::OpenStream(const string &fileName)
{
  this->fileName = new string(fileName);
  stream.open(fileName.c_str(), ios_base::in|ios_base::out|ios_base::ate);

  if (!stream.is_open())
  {
    stream.open(fileName.c_str(), ios_base::out|ios_base::app);
    stream.close();
    stream.open(fileName.c_str(), ios_base::in|ios_base::out|ios_base::ate);
  }
}

/* -------------------------------------------------------------------------- */

unsigned int OrgText::InternalWriteText(const string &text)
{
  unsigned int offset = 0;
  TextRegistry *deleted = SearchDeletedSpace(text.length());

  if (deleted == NULL)
  {
    // No deleted space available, so write at the end.
    stream.seekg(0, ios_base::end);
    offset = stream.tellg();
  }
  else
  {
    // Deleted space available, so write at that offset.
    stream.seekg(deleted->GetOffset(), ios_base::beg);
    offset = deleted->GetOffset();

    unsigned int deletedLength = deleted->GetLength() - text.length();
    unsigned int deletedOffset = deleted->GetOffset() + text.length();

    if (deletedLength > 0)
    {
      // Remains deleted space, so update the delete space.
      InternalDeleteText(deleted, deletedOffset, deletedLength);
    }
    else
    {
      // No more space at that offset, delete the registry.
      orgDeleted->DeleteRegistry(deleted->GetID());
    }

    delete deleted;
  }

  // Write the text.
  stream.write(text.c_str(), text.length());
  stream.flush();

  return offset;
}

/* -------------------------------------------------------------------------- */

TextRegistry* OrgText::SearchDeletedSpace(unsigned int length)
{
  try { orgDeleted->SeekRegistry(1); }
  catch (...) { return NULL; }

  TextRegistry *reg = NULL;
  TextRegistry *bestReg = NULL;

  // After pointing to the first registry, start seeking the best space.
  while((reg = dynamic_cast<TextRegistry*>(orgDeleted->GetNextRegistry())) != NULL)
  {
    // If the lengths are equal, is the perfect match;
    if (length == reg->GetLength())
    {
      if (bestReg != NULL)
        delete bestReg;

      return reg;
    }
    else if (bestReg == NULL && length <= reg->GetLength())
    {
      bestReg = reg;
    }
    // If text fits in reg and has more space than bestReg the frag is better.
    else if (length <= reg->GetLength() && reg->GetLength() > bestReg->GetLength())
    {
      delete bestReg;
      bestReg = reg;
    }
    else
    {
      delete reg;
    }
  }

  return bestReg;
}

/* -------------------------------------------------------------------------- */

void OrgText::InternalDeleteText(TextRegistry *reg, unsigned int offset, unsigned int length)
{
  TextRegistry *deleted = (reg == NULL) ? new TextRegistry() : reg;

  deleted->SetLength(length);
  deleted->SetOffset(offset);

  if (reg == NULL)
  {
    orgDeleted->WriteRegistry(*deleted);
    delete deleted;
  }
  else
  {
    orgDeleted->UpdateRegistry(*deleted);
  }
}

/* -------------------------------------------------------------------------- */

void OrgText::AssertStreamOpened() const
{
  if (!stream.is_open())
    throw "The text stream is not opened.";
}

/* -------------------------------------------------------------------------- */

void OrgText::AssertNotDeleted(const TextRegistry &reg) const
{
  if (reg.IsDeleted())
    throw "The text is marked as Deleted.";
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* OrgText::CreateTextRegistry()
{
  return new TextRegistry();
}

