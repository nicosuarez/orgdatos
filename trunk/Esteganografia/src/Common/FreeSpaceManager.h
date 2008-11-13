///////////////////////////////////////////////////////////
//  FreeSpaceManager.h
//  Implementation of the Class FreeSpaceManager
//  Created on:      13-Oct-2008 2:49:30 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B43D3F26_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B43D3F26_98EA_11dd_B49B_001B2425640C__INCLUDED_
#include "Space.h"
#include <list.h>
/**
 * Clase que se encarga de buscar dado un mensaje los mejores espacios libres
 * donde se puede guardar la informacion.
 */
class FreeSpaceManager
{

public:
	
	/* Devuelve la unica instancia de FreeSpaceManager (clase singleton) */
	FreeSpaceManager* GetInstance();
	
	/* Devuelve una lista de espacios libres en donde
	 * se puede almacenar un mensaje de tamaño "size" */
	list<Space>* GetFreeSpace(int size);
	
	/* Destructor */
	virtual ~FreeSpaceManager();

private:
	
	/*Puntero a la unica instancia del FreeSpaceManager*/
	static FreeSpaceManager* instance;
	
	/* Constructor privado */
	FreeSpaceManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
	FreeSpaceManager(const FreeSpaceManager &manager);
	FreeSpaceManager& operator=(const FreeSpaceManager &manager);
};
#endif // !defined(EA_B43D3F26_98EA_11dd_B49B_001B2425640C__INCLUDED_)
