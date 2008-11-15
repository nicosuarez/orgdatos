#ifndef LISTMSGREGISTRY_H_
#define LISTMSGREGISTRY_H_

#include "ListRegistry.h"

class ListMsgRegistry : public ListRegistry
{
public:
	ListMsgRegistry();
	
	ListMsgRegistry( ID_type idImage);
	
	virtual ~ListMsgRegistry();
	
	ID_type GetIDImage() const;
	
	unsigned int GetSize() const;
	
	void SetIDImage(ID_type idImage);
	
	char* Serialize() const;
	
	void Deserialize(const char* buffer, unsigned int length);
	
private:
	ID_type idImage;
	
    /* Allocation and copy constructor are private to prevent errors. */
	ListMsgRegistry(const ListMsgRegistry &Reg);
	ListMsgRegistry& operator=(const ListMsgRegistry &reg);
};

#endif /*LISTMSGREGISTRY_H_*/
