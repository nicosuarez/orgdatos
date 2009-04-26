#ifndef LISTSETSREGISTRY_H_
#define LISTSETSREGISTRY_H_

#include "ListRegistry.h"
#include <list>
#include <stdint.h>

class ListSetsRegistry: public ListRegistry {
public:

	ListSetsRegistry();

	ListSetsRegistry(ID_type idInitial, ID_type idSets);

	virtual ~ListSetsRegistry();

	static ExtensibleRelativeRegistry* Create();

	unsigned int GetSize() const;

	char* Serialize() const;

	void Deserialize(const char* buffer, unsigned int length);

	ID_type GetIdInitial()const;

	ID_type GetIdSets()const;

	void SetIdInitial(ID_type idInitial);

	void SetIdSets(ID_type idSets);

	std::list<ID_type>* GetListSets()const;

	void AddIdSet(ID_type idSet);

private:
	ID_type idInitial;
	uint32_t idSets;
};

#endif /* LISTSETSREGISTRY_H_ */
