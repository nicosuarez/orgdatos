#ifndef SETREGISTRY_H_
#define SETREGISTRY_H_

#include "ExtensibleRelativeRegistry.h"

class SetRegistry: public ExtensibleRelativeRegistry
{

public:

	SetRegistry();

	SetRegistry(ID_type offsetListWords);

	virtual ~SetRegistry();

	ID_type GetOffsetListWords() const;

	static ExtensibleRelativeRegistry* Create();

	void SetOffsetListWords(ID_type offsetListWords);

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
	ID_type offsetListWords;
};

#endif /* SETREGISTRY_H_ */
