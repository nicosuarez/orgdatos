#ifndef FREESPACEMANAGER_H_
#define FREESPACEMANAGER_H_
#include "Space.h"
#include "Constant.h"
#include "../Tree/factory.h"
#include "../Tree/BppTree/bpptree.h"
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Registries/FreeSpaceRegistry.h"
#include <list.h>

typedef std::list<Space*> tListSpaces;

/**
 * Clase que se encarga de buscar dado un mensaje los mejores espacios libres
 * donde se puede guardar la informacion.
 */
class FreeSpaceManager
{

public:
	
	/* Devuelve la unica instancia de FreeSpaceManager (clase singleton) */
	static FreeSpaceManager* GetInstance();
	
	/* Devuelve una lista de espacios libres en donde
	 * se puede almacenar un mensaje de tamaño "size" */
	tListSpaces* GetFreeSpaces(unsigned long size);
	
	/* Destructor */
	virtual ~FreeSpaceManager();
	
	/* Agrega un espacio nuevo disponible */
	ID_type AddFreeSpace(Space* space);
	
	/* Agrega una lista de espacios disponible */
	ID_type AddFreeSpaces(tListSpaces* space);

private:
	
	OrgExtensibleRelative orgFreeSpaces;
	BppTree freeSpacesTree;
	
	/*Puntero a la unica instancia del FreeSpaceManager*/
	static FreeSpaceManager* instance;
	
	/* Constructor privado */
	FreeSpaceManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
	FreeSpaceManager(const FreeSpaceManager &manager);
	FreeSpaceManager& operator=(const FreeSpaceManager &manager);
};
#endif // FREESPACEMANAGER_H_
