#ifndef WORDREGISTRY_H_
#define WORDREGISTRY_H_

#include "ExtensibleRelativeRegistry.h"

class WordRegistry: public ExtensibleRelativeRegistry
{

public:

	WordRegistry();

	WordRegistry(ID_type idListSets);

	virtual ~WordRegistry();

	static ExtensibleRelativeRegistry* Create();

	ID_type GetIdListSets() const;

	void SetIdListSets(ID_type idListSets);

	/* Gets the size of the registry */
    unsigned int GetSize() const;

    /* Gets the char pointer that represents the serialization of the
     * registry. The allocated memory must be freed by the caller. */
    char* Serialize() const;

    /* Load all the attributes of the registry from the serialization.
     * buffer: The serialized registry.
     * length: Length of the serialization. */
    void Deserialize(const char* buffer, unsigned int length);

private:
	ID_type idListSets;
};

#endif /* WORDREGISTRY_H_ */
