/* -------------------------------------------------------------------------- */
// ListRegistry.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _LIST_REGISTRY_
#define _LIST_REGISTRY_

#include "ExtensibleRelativeRegistry.h"

/* This class represents the registry that will be used in the organization 
 * OrgList. It inherits ExtensibleRelativeRegistry and override methods. */
class ListRegistry : public ExtensibleRelativeRegistry
{
  public:
    /* Constructor. */ 
    ListRegistry();

    /* Destructor. */ 
    virtual ~ListRegistry();

    /* Gets the next ID of the registry in the list. */
    ID_type GetNextID() const;

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

  private:
    ID_type nextId;

    /* Sets the ID of the next registry in the list. 
     * id: ID of the next registry in the list. */
    void SetNextID(ID_type id);

    /* Allocation and copy constructor are private to prevent errors. */
    ListRegistry(const ListRegistry &reg);
    ListRegistry& operator=(const ListRegistry &reg);

    // Friend class that will use SetNextID method.    
    friend class OrgList;
};
#endif

