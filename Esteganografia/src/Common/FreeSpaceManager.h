#ifndef FREESPACEMANAGER_H_
#define FREESPACEMANAGER_H_
#include "Space.h"
#include "Constant.h"
#include "ImageManager.h"
#include "../Tree/factory.h"
#include "../Tree/BppTree/bpptree.h"
#include "../DataAccess/Organizations/OrgList.h"
#include "../DataAccess/Registries/ListFreeSpaceRegistry.h"
#include "../Steganographic/Image.h"
#include "../Steganographic/ImageFactory.h"
#include "Exception/eFile.h"
#include "Exception/eNotSpace.h"
#include <list>

typedef std::list<Space*> tListSpaces;
typedef std::list<Space*>::iterator itListSpaces;
typedef std::vector< Space* > tVecFreeSpace;

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

	/* Elimina un espacio libre de una imagen */
	void RemoveFreeSpace(Space* freeSpace);

	/* Destructor */
	virtual ~FreeSpaceManager();

	/* Agrega un espacio nuevo disponible */
	ID_type AddFreeSpace(Space* space);

	/* Agrega una lista de espacios disponible */
	void AddFreeSpaces(tListSpaces* spacesList);
	
	/* Elimina una lista de espacios libres */
	void RemoveFreeSpace(tVecFreeSpace& freeSpaceList);
	
	/* Elimina una lista espacios libres de una imagen */
	void RemoveFreeSpaceList(ID_type ptrFreeSpace);
	
	/* Obtiene la lista de espacios libres de una imagen */
	tRegisterList* GetFreeSpacesList(ID_type ptrFreeSpace);

private:

	OrgList orgListFreeSpaces;
	BppTree freeSpacesTree;

	/*Puntero a la unica instancia del FreeSpaceManager*/
	static FreeSpaceManager* instance;

	void PrintIteratorValue(TreeIterator& it);
	
	ListFreeSpaceRegistry* FindSpaceConsecutive(tRegisterList* freeSpaceList, Space* space, unsigned long &newPosition, unsigned long &newSpaceSize);

	/* Constructor privado */
	FreeSpaceManager();

	/*Constructor de copia y operador = privados para evitar errores*/
	FreeSpaceManager(const FreeSpaceManager &manager);
	FreeSpaceManager& operator=(const FreeSpaceManager &manager);
};
#endif // FREESPACEMANAGER_H_
