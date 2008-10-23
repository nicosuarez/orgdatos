///////////////////////////////////////////////////////////
//  Image.h
//  Implementation of the Class Image
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "IStenographic.h"

typedef char UBYTE;

/**
 * Clase que agrupa todos los formatos de imagenes disponibles.
 */
class Image : public IStenographic
{

public:
	Image(char* filePath);
	Image();
	virtual bool ValidateFormat(Space* space);
	virtual ~Image();
	
	long GetId() const{
		return imageId;
	}
	
	long GetDirectoryId() const{
		return directoryId;
	}
	
	long GetNameId() const{
		return nameId;
	}
	
	long GetFirstFreeSpaceId() const{
		return firstFreeSpaceId;
	}
	
	long GetLastFreeSpaceId() const{
		return lastFreeSpaceId;
	}
	
	long GetMaxFreeSpaceSize() const{
		return maxFreeSpaceSize;
	}
	
protected:
	long imageId;
	long directoryId;
	long nameId;
	long firstFreeSpaceId;
	long lastFreeSpaceId;
	long maxFreeSpaceSize;
	char* filePath;

};
#endif // !defined(EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_)
