/* -------------------------------------------------------------------------- */
// ExtensibleRelativeFile.cpp
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#include "ExtensibleRelativeFile.h"

ExtensibleRelativeFile::ExtensibleRelativeFile(const string &fileName, ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)())
{
  this->fileName = new string(fileName);
  this->ptrMethodCreateRegistry = ptrMethodCreateRegistry;
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeFile::~ExtensibleRelativeFile()
{
  Close();
  delete(fileName);
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Create(unsigned int size)
{
  AssertFileClosed();

  if (Exists())
    throw "The file you want to create already exists.";

  // Create the file if it doesn't exist and write the header.
  const char *c_fileName = (*fileName).c_str();
  file.open(c_fileName, ios_base::out);

  newID = 1;
  nextID = 0;
  this->size = size;

  WriteHeader();
  Close();
}

/* -------------------------------------------------------------------------- */

bool ExtensibleRelativeFile::Exists()
{
  // If it is already open, return true.
  if (file.is_open())
    return true;

  // Try to open the file without creating it.
  const char *c_fileName = (*fileName).c_str();
  file.open(c_fileName, ios_base::in);

  if (file.is_open())
  {
    file.close();
    return true;
  }

  return false;
}

/* -------------------------------------------------------------------------- */

bool ExtensibleRelativeFile::IsOpen() const
{
  return file.is_open();
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Open(short mode)
{
  AssertFileClosed();
  const char *c_fileName = (*fileName).c_str();

  // The Write mode also opens the file for reading, to recover the header.
  switch (mode)
  {
    case READ:
      file.open(c_fileName, ios_base::in|ios_base::binary);
      break;
    case WRITE:
    case READ_WRITE:
      file.open(c_fileName, ios_base::in|ios_base::out|ios_base::binary);
      break;
    default:
      throw "Trying to open a file with an incorrect open mode.";
  }

  AssertFileOpened();

  // Recover the header and set the open mode.
  ReadHeader();
  openMode = mode;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Seek(ID_type id)
{
  AssertRangeID(id);

  readNextID = id;
  InternalSeek(id);
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* ExtensibleRelativeFile::Read(ID_type id)
{
  AssertRead(id);

  ExtensibleRelativeRegistry *reg = InternalRead(id);

  if (reg->IsDeleted())
  {
    // If the registry is deleted, set the original ID.
    reg->SetID(id);
  }

  return reg;
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* ExtensibleRelativeFile::ReadNext()
{
  AssertFileOpened();

  while (readNextID < newID)
  {
    ExtensibleRelativeRegistry *reg = InternalRead(readNextID);
    ++readNextID;

    if (!reg->IsDeleted())
      return reg;

    delete reg;
  }

  return NULL;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Write(ExtensibleRelativeRegistry &reg)
{
  AssertWrite(reg);

  /* If nextID is greater than 0, the new registry will occupy a deleted one.
   * If not, it will be given a new ID. */
  int id = (nextID > 0) ? nextID : newID;
  reg.SetID(id);

  if (nextID > 0)
  {
    // Recover the next deleted ID in order to reuse them.
    ExtensibleRelativeRegistry *deleted = InternalRead(nextID); 
    nextID = deleted->GetID();
    delete deleted;
  }
  else
  {
    // Increase the ID for the next ones.
    newID++;
  }

  InternalWrite(reg, reg.GetID());
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Update(const ExtensibleRelativeRegistry &reg)
{
  AssertWrite(reg);
  ExtensibleRelativeRegistry *existent = InternalRead(reg.GetID());

  if (existent->IsDeleted())
    throw "The registry to update is marked as Deleted.";

  delete existent;

  InternalWrite(reg, reg.GetID());
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Delete(ID_type id)
{
  ExtensibleRelativeRegistry *reg = InternalRead(id);
  AssertWrite(*reg);

  reg->SetID(nextID);
  reg->SetDeleted();

  nextID = id;
  InternalWrite(*reg, id);

  delete reg;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Close()
{
  if (IsOpen())
    file.close();
  
  size = 0;
  newID = 0;
  nextID = 0;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::Destroy()
{
  Close();
  remove((*fileName).c_str());
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::InternalSeek(ID_type id)
{
  unsigned int offset = (size * (id - 1)) + GetHeaderOffset();
  file.seekg(offset, ios_base::beg);
}

/* -------------------------------------------------------------------------- */

ExtensibleRelativeRegistry* ExtensibleRelativeFile::InternalRead(ID_type id)
{
  ExtensibleRelativeRegistry *reg = (*ptrMethodCreateRegistry)();

  InternalSeek(id);
  char *buffer = new char[size];

  file.read(buffer, size);
  reg->Deserialize(buffer, size);
  
  delete[] buffer;
  return reg;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::InternalWrite(const ExtensibleRelativeRegistry &reg, ID_type id)
{
  WriteHeader();
  InternalSeek(id);

  char *buffer = reg.Serialize();
  file.write(buffer, size);

  file.flush();
  delete[] buffer;
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::ReadHeader()
{
  AssertFileOpened();

  file.seekg(0, ios_base::beg);
  file.read(reinterpret_cast<char*>(&size), sizeof(size));
  file.read(reinterpret_cast<char*>(&newID), sizeof(newID));
  file.read(reinterpret_cast<char*>(&nextID), sizeof(nextID));
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::WriteHeader()
{
  AssertFileOpened();

  file.seekg(0, ios_base::beg);
  file.write(reinterpret_cast<char*>(&size), sizeof(size));
  file.write(reinterpret_cast<char*>(&newID), sizeof(newID));
  file.write(reinterpret_cast<char*>(&nextID), sizeof(nextID));
}

/* -------------------------------------------------------------------------- */

unsigned int ExtensibleRelativeFile::GetHeaderOffset() const
{
  return sizeof(size) + sizeof(newID) + sizeof(nextID);
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::AssertFileOpened() const
{
  if (!IsOpen())
    throw "The file is closed.";
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::AssertFileClosed() const
{
  if (IsOpen())
    throw "The file is open.";
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::AssertRead(ID_type id) const
{
  AssertRangeID(id);
  AssertFileOpened();

  if (openMode == WRITE)
    throw "The file is opened just for Write.";
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::AssertRangeID(ID_type id) const
{
  if (id < 1 || id >= newID)
    throw "The ID is out of the valid range.";
}

/* -------------------------------------------------------------------------- */

void ExtensibleRelativeFile::AssertWrite(const ExtensibleRelativeRegistry &reg) const
{
  AssertFileOpened();

  if (reg.GetSize() != size)
    throw "The registry size and the serialization size are different.";

  if (openMode == READ)
    throw "The file is opened just for Read.";

  if (reg.IsDeleted())
    throw "The registry is marked as Deleted.";
}

