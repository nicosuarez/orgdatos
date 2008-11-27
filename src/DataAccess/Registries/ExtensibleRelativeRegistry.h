/* -------------------------------------------------------------------------- */
// ExtensibleRelativeRegistry.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _EXTENSIBLE_RELATIVE_REGISTRY_
#define _EXTENSIBLE_RELATIVE_REGISTRY_

#include "../Files/Serializable.h"
#include "../../Common/Resource.h"


/* This class represents the registry that will be saved in a file of 
 * type ExtensibleRelativeFile. It inherits Serializable, so it 
 * must be of fixed size. */
class ExtensibleRelativeRegistry : public Serializable
{
  public:
    /* Constructor. */ 
    ExtensibleRelativeRegistry();

    /* Destructor. */ 
    virtual ~ExtensibleRelativeRegistry();

    /* Gets the ID of the registry inside the file. */
    ID_type GetID() const;

    /* Checks if the registry is Deleted. */
    bool IsDeleted() const;

    /* Gets the size of the registry.
     * Each derived class should specify its size. */
    virtual unsigned int GetSize() const;

    /* Gets the char pointer that represents the serialization of the 
     * registry. Each derived class will have to call this method and also 
     * serialize their own fields. The allocated memory must be freed 
     * by the caller. */
    virtual char* Serialize() const;

    /* Load all the attributes of the registry from the serialization.
     * Each derived class will have to call this method and also 
     * deserialize their own fields. 
     * buffer: The serialized registry. 
     * length: Length of the serialization. */
    virtual void Deserialize(const char* buffer, unsigned int length);

  protected:
    /* Sets the ID of the registry inside the file. 
     * id: ID of the registry inside the file. */
    void SetID(ID_type id);

    /* Mark the registry as Deleted. */
    void SetDeleted();
  
  private:
    ID_type id;

    char adminFlags;
    static const short DELETED = 0x1;

    /* Allocation and copy constructor are private to prevent errors. */
    ExtensibleRelativeRegistry(const ExtensibleRelativeRegistry &reg);
    ExtensibleRelativeRegistry& operator=(const ExtensibleRelativeRegistry &reg);

    // Friend class that will use SetID and SetDeleted methods.    
    friend class ExtensibleRelativeFile;
};
#endif

