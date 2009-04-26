#ifndef LISTBLACKWORDREGISTRY_H_
#define LISTBLACKWORDREGISTRY_H_

#include "ListRegistry.h"

class ListBlackWordRegistry: public ListRegistry {
public:

	ListBlackWordRegistry();

	ListBlackWordRegistry(ID_type idWord);

	virtual ~ListBlackWordRegistry();

	static ExtensibleRelativeRegistry* Create();

	unsigned int GetSize() const;

	char* Serialize() const;

	void Deserialize(const char* buffer, unsigned int length);

	ID_type GetIdWord()const;

	void SetIdWord(ID_type idWord);

private:
	ID_type idWord;
};

#endif /* LISTBLACKWORDREGISTRY_H_ */
