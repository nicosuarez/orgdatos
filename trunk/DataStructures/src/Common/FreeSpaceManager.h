///////////////////////////////////////////////////////////
//  FreeSpaceManager.h
//  Implementation of the Class FreeSpaceManager
//  Created on:      13-Oct-2008 2:49:30 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B43D3F26_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B43D3F26_98EA_11dd_B49B_001B2425640C__INCLUDED_

/**
 * Clase que se encarga de buscar dado un mensaje los mejores espacios libres
 * donde se puede guardar la informacion.
 */
class FreeSpaceManager
{

public:
	FreeSpaceManager();
	virtual ~FreeSpaceManager();

	List<Space> GetFreeSpace(int size);

};
#endif // !defined(EA_B43D3F26_98EA_11dd_B49B_001B2425640C__INCLUDED_)
