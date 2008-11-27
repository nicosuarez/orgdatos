/* -------------------------------------------------------------------------- */
// Serializable.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _SERIALIZABLE_
#define _SERIALIZABLE_

#include <string>

/* This abstract class gives the possibility to serialize the 
 * derived classes. The registry to serialize must be of fixed size. */
class Serializable
{
  public:
    /* Gets the size of the registry. 
     * Each derived class specifies its size. */
    virtual unsigned int GetSize() const = 0;
  
    /* Gets the char pointer that represents the serialization of the 
     * registry. Each derived class will know how to serialize itself. 
     * The allocated memory must be freed by the caller. */
    virtual char* Serialize() const = 0;

    /* Load all the attributes of the registry from the serialization.
     * Each derived class will know how to deserialize itself. 
     * buffer: The serialized registry. 
     * length: Length of the serialization. */
    virtual void Deserialize(const char* buffer, unsigned int length) = 0;

  protected:
    /* Constructor and Destructor. */
    Serializable();
    virtual ~Serializable();

    /* Adds an attribute to the serialization.
     * buffer: The serialization.
     * item: The item to add.
     * pos: Position where the item will be added.
     * length: Length in bytes of the item to add. */
    void AddToSerialization(char *buffer, const void *item, unsigned int pos, unsigned int length) const;

    /* Gets an attribute from serialization.
     * buffer: The serialization.
     * item: The item where it will be recovered.
     * pos: Position where the item is.
     * length: Length in bytes of the item to recover. */
    void GetFromSerialization(const char *buffer, void *item, unsigned int pos, unsigned int length) const;

  private:
    /* Allocation and copy constructor are private to prevent errors. */
    Serializable(const Serializable &serializable);
    Serializable& operator=(const Serializable &serializable);
};
#endif

