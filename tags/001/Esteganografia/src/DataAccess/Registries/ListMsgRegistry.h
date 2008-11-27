#ifndef LISTMSGREGISTRY_H_
#define LISTMSGREGISTRY_H_

#include "ListRegistry.h"

class ListMsgRegistry : public ListRegistry
{
public:
	ListMsgRegistry();
	
	ListMsgRegistry( ID_type idMsg);
	
	virtual ~ListMsgRegistry();
	
	static ExtensibleRelativeRegistry* Create();
	
	ID_type GetIDMessage() const;
	
	unsigned int GetSize() const;
	
	void SetIDMessage(ID_type idMsg);
	
	char* Serialize() const;
	
	void Deserialize(const char* buffer, unsigned int length);
	
private:
	ID_type idMsg;
	
    /* Allocation and copy constructor are private to prevent errors. */
	ListMsgRegistry(const ListMsgRegistry &Reg);
	ListMsgRegistry& operator=(const ListMsgRegistry &reg);
};

#endif /*LISTMSGREGISTRY_H_*/
