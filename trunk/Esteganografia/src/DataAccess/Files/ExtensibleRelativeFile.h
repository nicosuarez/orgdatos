/* -------------------------------------------------------------------------- */
// ExtensibleRelativeFile.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _EXTENSIBLE_REALTIVE_FILE_
#define _EXTENSIBLE_REALTIVE_FILE_

#include <string>
#include <fstream>
#include "../Registries/ExtensibleRelativeRegistry.h"

using namespace std;

/* This file will store registries of type ExtensibleRelativeRegistry that 
 * are of fixed size. This file is like a relative file, using ID to 
 * identify the registries. */
class ExtensibleRelativeFile
{
  public:
    /* Constructor. 
     * filename: Name of the file. 
     * ptrMethodCreateRegistry: Pointer to a method that return a 
     * pointer to a new ExtensibleRelativeRegistry. */
    ExtensibleRelativeFile(const string &fileName, ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)());

    /* Destructor. */ 
    virtual ~ExtensibleRelativeFile();

    /* Creates the file if it doesn not exist and write the header. 
     * size: Size of the registry. */ 
    void Create(unsigned int size);

    /* Returns true if the file exists. */
    bool Exists();

    /* Returns true if the file is open or false if not. */
    bool IsOpen() const;

    /* Opens the file according to the mode.
     * mode: The opening mode of the file. */
    void Open(short mode);

    /* Seeks the registry with the ID. 
     * id: The ID of the registry. */
    void Seek(ID_type id);

    /* Reads the registry with the ID from the file. 
     * The allocated memory must be freed by the caller.
     * id: The ID of the registry to read. */
    ExtensibleRelativeRegistry* Read(ID_type id);

    /* Reads the next not deleted registry until the end of the file (NULL). 
     * Before using this method Seek must be used to positionate the file. 
     * The allocated memory must be freed by the caller. */
    ExtensibleRelativeRegistry* ReadNext();

    /* Writes the registry to the file. 
     * reg: The registry to write. */
    void Write(ExtensibleRelativeRegistry &reg);

    /* Updates the registry to the file. 
     * reg: The registry to update. */
    void Update(const ExtensibleRelativeRegistry &reg);

    /* Deletes (logic) the registry with the ID from the file. 
     * id: The ID of the registry to delete. */
    void Delete(ID_type id);

    /* Closes the file. */
    void Close();

    /* Deletes the file. */
    void Destroy();

    /* Open modes. */
    static const short READ = 0;
    static const short WRITE = 1;
    static const short READ_WRITE = 2;

  private:
    fstream file;
    short openMode;
    const string *fileName;
    
    // ID that is used in the ReadNext.
    ID_type readNextID;
    
    // Pointer to the function that creates the specific registry.
    ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)();

    // These two IDs and the size are in the header.
    ID_type newID;
    ID_type nextID;
    unsigned int size;

    /* Some methods to manage the file internally. */
    void InternalSeek(ID_type id);
    ExtensibleRelativeRegistry* InternalRead(ID_type id);
    void InternalWrite(const ExtensibleRelativeRegistry &reg, ID_type id);

    /* Some methods to manage the header of the file. */
    void ReadHeader();
    void WriteHeader();
    unsigned int GetHeaderOffset() const;

    /* Asserts. */
    void AssertFileOpened() const;
    void AssertFileClosed() const;
    void AssertRead(ID_type id) const;
    void AssertRangeID(ID_type id) const;
    void AssertWrite(const ExtensibleRelativeRegistry &reg) const;

    /* Allocation and copy constructor are private to prevent errors. */
    ExtensibleRelativeFile(const ExtensibleRelativeFile &file);
    ExtensibleRelativeFile& operator=(const ExtensibleRelativeFile &file);
};
#endif

