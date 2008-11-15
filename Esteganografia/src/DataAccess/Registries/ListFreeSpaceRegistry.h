#ifndef LISTFREESPACEREGISTRY_H_
#define LISTFREESPACEREGISTRY_H_

#include "ListRegistry.h"

class ListFreeSpaceRegistry : public ListRegistry
{
public:
	ListFreeSpaceRegistry();
	
	ListFreeSpaceRegistry(unsigned long offsetImage, unsigned long sizeFreeSpace);
	
	virtual ~ListFreeSpaceRegistry();
	
	static ExtensibleRelativeRegistry* Create();
	
	unsigned long GetOffsetImage() const;
	
	unsigned long GetSizeFreeSpace() const;
	
	unsigned int GetSize() const;
	
	void SetOffsetImage(unsigned long offsetImage);
	
	void SetSizeFreeSpace(unsigned long sizeFreeSpace);
	
	char* Serialize() const;
	
	void Deserialize(const char* buffer, unsigned int length);
		
private:
	
	unsigned long offsetImage;
	unsigned long sizeFreeSpace;
	
    /* Allocation and copy constructor are private to prevent errors. */
	ListFreeSpaceRegistry(const ListFreeSpaceRegistry &Reg);
	ListFreeSpaceRegistry& operator=(const ListFreeSpaceRegistry &reg);
};

#endif /*LISTFREESPACEREGISTRY_H_*/
