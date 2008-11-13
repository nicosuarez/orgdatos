/* -------------------------------------------------------------------------- */
// OrgExtensibleRelative.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _ORG_EXTENSIBLE_RELATIVE_
#define _ORG_EXTENSIBLE_RELATIVE_

#include <string>
#include "../Files/ExtensibleRelativeFile.h"
#include "../Registries/ExtensibleRelativeRegistry.h"

/* This class handles the ExtensibleRelativeFile as an organization.
 * This particularly uses directly the file methods.  */
class OrgExtensibleRelative
{
  public:
    /* Constructor. 
     * filename: Name of the file that the organization uses. 
     * ptrMethodCreateRegistry: Pointer to a method that return a 
     * pointer to a new ExtensibleRelativeRegistry. */
    OrgExtensibleRelative(const string &fileName, ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)());

    /* Destructor. */ 
    virtual ~OrgExtensibleRelative();

    /* Seeks the registry with the ID. 
     * id: The ID of the registry. */
    void SeekRegistry(ID_type id);

    /* Gets a registry with the ID from the organization. 
     * The allocated memory must be freed by the caller.
     * id: The ID of the registry to get. */
    ExtensibleRelativeRegistry* GetRegistry(ID_type id);

    /* Reads the next not deleted registry until the end, when it 
     * returns NULL. Before using this method SeekRegistry must 
     * be used to positionate the file. The allocated memory must be 
     * freed by the caller. */
    ExtensibleRelativeRegistry* GetNextRegistry();

    /* Writes the registry to the organization. 
     * reg: The registry to write. */
    void WriteRegistry(ExtensibleRelativeRegistry &reg);

    /* Updates the registry in the organization. 
     * reg: The registry to update. */
    void UpdateRegistry(const ExtensibleRelativeRegistry &reg);

    /* Deletes the registry with the ID from the organization. 
     * id: The ID of the registry to delete. */
    void DeleteRegistry(ID_type id);

    /* Destroys the organization deleting all the files. */
    void Destroy();

  private:
    ExtensibleRelativeFile *file;

    /* Allocation and copy constructor are private to prevent errors. */
    OrgExtensibleRelative(const OrgExtensibleRelative &org);
    OrgExtensibleRelative& operator=(const OrgExtensibleRelative &org);
};

#endif

