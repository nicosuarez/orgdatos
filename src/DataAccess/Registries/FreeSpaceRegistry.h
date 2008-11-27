#ifndef FREESPACEREGISTRY_H_
#define FREESPACEREGISTRY_H_

#include "ExtensibleRelativeRegistry.h"

class FreeSpaceRegistry : public ExtensibleRelativeRegistry
{
public:
	FreeSpaceRegistry();
	virtual ~FreeSpaceRegistry();
	
	static ExtensibleRelativeRegistry* Create();
	
private:
	
    /* Allocation and copy constructor are private to prevent errors. */
	FreeSpaceRegistry(const FreeSpaceRegistry &Reg);
    FreeSpaceRegistry& operator=(const FreeSpaceRegistry &reg);
	
};

#endif /*FREESPACEREGISTRY_H_*/
