#include "RemoveDirectory.h"
#include "../Common/ImageManager.h"
#include "../Common/Resource.h"

using namespace std;

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
		cout<<FIRST_MSG_REMOVE_DIRECTORY<<"\n";
	else
		cout<<ERR_MSG_REMOVE_DIRECTORY<<"\n";
	for (unsigned int i=0;i<lDir.size();i++){
		cout<<lDir[i]<<"\n";
	}
	return true;
}
