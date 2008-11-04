///////////////////////////////////////////////////////////
//  Image.h
//  Implementation of the Class Image
//  Created on:      13-Oct-2008 2:49:31 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "IStenographic.h"
#include "../Common/Resource.h"
#include <list>

typedef char UBYTE;
typedef std::list<Space*> tListSpaces;

/**
 * Clase que agrupa todos los formatos de imagenes disponibles.
 */
class Image : public IStenographic
{

public:
	Image(const char* filePath);
	Image();
	virtual bool Load();
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
	
	const char* GetFilePath() const{
		return filePath;
	}
	
	/**
	 * Tamano total en bytes del archivo donde esta contenido el espacio.
	 */
	long GetTotalSize() const;
	
	
protected:
	long imageId;
	long directoryId;
	long nameId;
	long firstFreeSpaceId;
	long lastFreeSpaceId;
	long maxFreeSpaceSize;
	long initialPosition;
	const char* filePath;

};
#endif // !defined(EA_B4E5CF88_98EA_11dd_B49B_001B2425640C__INCLUDED_)
