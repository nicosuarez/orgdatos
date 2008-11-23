#ifndef LISTFREESPACEREGISTRY_H_
#define LISTFREESPACEREGISTRY_H_

#include "ListRegistry.h"

class ListFreeSpaceRegistry : public ListRegistry
{
public:
	ListFreeSpaceRegistry();
	
	ListFreeSpaceRegistry(ID_type idImg);
	
	virtual ~ListFreeSpaceRegistry();
	
	static ExtensibleRelativeRegistry* Create();
	
	ID_type GetIdImage() const;
	
	unsigned int GetSize() const;
	
	void SetIdImage(ID_type idImg);
	
	char* Serialize() const;
	
	void Deserialize(const char* buffer, unsigned int length);
		
private:
	
	unsigned long idImage;
	
    /* Allocation and copy constructor are private to prevent errors. */
	ListFreeSpaceRegistry(const ListFreeSpaceRegistry &Reg);
	ListFreeSpaceRegistry& operator=(const ListFreeSpaceRegistry &reg);
};

#endif /*LISTFREESPACEREGISTRY_H_*/
