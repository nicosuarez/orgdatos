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
	tListSpaces * lista = new tListSpaces();
	Image * image = ImageFactory::GetImage("./Images/BMP256Colores.bmp");
	lista->push_front(image->Load());
	delete image;
	return lista;
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

