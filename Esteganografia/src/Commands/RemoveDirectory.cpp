#include "RemoveDirectory.h"
#include "../Common/ImageManager.h"
#include "../Common/Resource.h"

RemoveDirectory::RemoveDirectory(string cmd) : Command(cmd)
{

}

RemoveDirectory::RemoveDirectory() : Command(" ")
{

}

RemoveDirectory::~RemoveDirectory()
{
}

/**
 * Muestra la ayuda del comando.
 */
void RemoveDirectory::ShowHelpCommand()
{
	cout << HLP_REMOVE_DIRECTORY << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool RemoveDirectory::InternalProcess(tVecStr params)
{
	string path = params[1];
	ImageManager* img=ImageManager::GetInstance();
	tVecStr lDir=img->DeleteDirectory(path.c_str());
	if (lDir.size()>0)
	{
		cout << "\n" << FIRST_MSG_REMOVE_DIRECTORY <<"\n\n";
	}
	for (unsigned int i=0;i<lDir.size();i++)
	{
		cout<< "\t" << CIRCLE << lDir[i]<<"\n";
	}
	cout << "\n";
	return true;
}
