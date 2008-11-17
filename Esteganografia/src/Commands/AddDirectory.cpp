#include "AddDirectory.h"
#include "../Common/ImageManager.h"

using namespace std;

AddDirectory::AddDirectory(string cmd) : Command(cmd)
{

}

AddDirectory::AddDirectory() : Command(" ")
{

}

AddDirectory::~AddDirectory()
{
}

/**
 * Muestra la ayuda del comando.
 */
void AddDirectory::ShowHelpCommand()
{
	cout << HLP_ADD_DIRECTORY << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool AddDirectory::InternalProcess(tVecStr params)
{
	string path = params[1];
	tVecStr fileList = FileSystem::GetFiles(path.c_str(), File);	
	ImageManager* iManager=ImageManager::GetInstance();
	iManager->AddDirectory(path.c_str());
	return true;
}
