#include "FreeSpaceRegistry.h"

FreeSpaceRegistry::FreeSpaceRegistry()
{
}

FreeSpaceRegistry::~FreeSpaceRegistry()
{
}

ExtensibleRelativeRegistry* FreeSpaceRegistry::Create()
{
	return new FreeSpaceRegistry(); 
}
