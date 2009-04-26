/* -------------------------------------------------------------------------- */
// TextRegistry.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _TEXT_REGISTRY_
#define _TEXT_REGISTRY_

#include "ExtensibleRelativeRegistry.h"

/* This class represents the registry that will be used in the organization 
 * OrgText. It inherits ExtensibleRelativeRegistry and override methods. */
class TextRegistry : public ExtensibleRelativeRegistry
{
  public:
    /* Constructor. */ 
    TextRegistry();

    /* Destructor. */ 
    virtual ~TextRegistry();

    /* Gets the offset of the text in the file. */
    unsigned int GetOffset() const;

    /* Gets the length of the text. */
    unsigned int GetLength() const;

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
    unsigned int offset;
    unsigned int length;

    /* Sets the offset of the text in the file.
     * offset: Offset of the text in the file. */
    void SetOffset(unsigned int offset);

    /* Sets the length of the text.
     * length: Length of the text. */
    void SetLength(unsigned int length);

    /* Allocation and copy constructor are private to prevent errors. */
    TextRegistry(const TextRegistry &reg);
    TextRegistry& operator=(const TextRegistry &reg);

    // Friend class that will use SetOffset and SetLength methods.    
    friend class OrgText;
};
#endif

