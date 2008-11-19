#ifndef FREESPACEMANAGER_H_
#define FREESPACEMANAGER_H_
#include "Space.h"
#include "Constant.h"
#include "ImageManager.h"
#include "../Tree/factory.h"
#include "../Tree/BppTree/bpptree.h"
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Registries/FreeSpaceRegistry.h"
#include "../Steganographic/Image.h"
#include "../Steganographic/ImageFactory.h"
#include "Exception/eFile.h"
#include <list.h>

typedef std::list<Space*> tListSpaces;
typedef std::list<Space*>::iterator itListSpaces;
typedef std::vector<KeyFreeSpace*> tVecKFreeSpace;
typedef std::vector<Space*> tVecNewFreeSpaces;

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

	/* Agrega un espacio libre al arbol */
//	void AddFreeSpaceTree(ID_type idFreeSpace, unsigned long size,
//			ID_type idImg, unsigned long position);

	/* Destructor */
	virtual ~FreeSpaceManager();

	/* Agrega un espacio nuevo disponible */
	ID_type AddFreeSpace(Space* space);

	/* Agrega una lista de espacios disponible */
	void AddFreeSpaces(tListSpaces* spacesList);

private:

	OrgExtensibleRelative orgFreeSpaces;
	BppTree freeSpacesTree;

	/*Puntero a la unica instancia del FreeSpaceManager*/
	static FreeSpaceManager* instance;

	void PrintIteratorValue(TreeIterator& it);

	/* Constructor privado */
	FreeSpaceManager();

	/*Constructor de copia y operador = privados para evitar errores*/
	FreeSpaceManager(const FreeSpaceManager &manager);
	FreeSpaceManager& operator=(const FreeSpaceManager &manager);
};
#endif // FREESPACEMANAGER_H_
