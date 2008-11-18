#include "FreeSpaceManager.h"

FreeSpaceManager* FreeSpaceManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


FreeSpaceManager::FreeSpaceManager() :  orgFreeSpaces(PATH_FREE_SPACE_FILE, FreeSpaceRegistry::Create),
										freeSpacesTree(512,KeyFreeSpaceFactory(), ValueFreeSpaceFactory(),PATH_TREE_FREE_SPACE)
{
	delete instance;
}
/* -------------------------------------------------------------------------- */


FreeSpaceManager* FreeSpaceManager::GetInstance()
{
	if(instance == NULL)
		instance = new FreeSpaceManager();
	return instance;
}
/* -------------------------------------------------------------------------- */
FreeSpaceManager::~FreeSpaceManager()
{

}
/* -------------------------------------------------------------------------- */
tListSpaces* FreeSpaceManager::GetFreeSpaces(unsigned long size)
{
	
	//TreeIterator& it = freeSpacesTree.iterator();
	
	/*codigo de prueba*/
	tListSpaces * lista = new tListSpaces();
	Image * image = ImageFactory::GetImage("./Images/GIF_87a.gif");
	Space *space = image->Load();
	cout << "Tamaño del espacio: " << space->GetSize() << endl;
	lista->push_front(space);
	delete image;
	
	image = ImageFactory::GetImage("./Images/GIF_boxe06.gif");
	space = image->Load();
	cout << "Tamaño del espacio: " << space->GetSize() << endl;
	lista->push_back(space);
	delete image;
	return lista;
	/*fin de codigo de prueba*/
}
/* -------------------------------------------------------------------------- */
ID_type AddFreeSpaces(tListSpaces* space)
{
	return 1;
}
/* -------------------------------------------------------------------------- */
ID_type FreeSpaceManager::AddFreeSpace(Space* space)
{
	FreeSpaceRegistry fsReg;
	orgFreeSpaces.WriteRegistry(fsReg);
	
	return fsReg.GetID();	
}
/* -------------------------------------------------------------------------- */
void FreeSpaceManager::AddFreeSpaceTree(ID_type idFreeSpace, unsigned long size,
			ID_type idImg, unsigned long position)
{
	KeyFreeSpace keyFs(idFreeSpace, size);
	ValueFreeSpace valFs(idImg, position);
	freeSpacesTree.insert(keyFs, valFs);
	
	cout << freeSpacesTree << "\n";
}
/* -------------------------------------------------------------------------- */

