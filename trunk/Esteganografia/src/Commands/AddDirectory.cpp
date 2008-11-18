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
	ImageManager* iManager=ImageManager::GetInstance();
	tVecStr vec =iManager->AddDirectory(path.c_str());
	if (vec.size()!=0)
		cout<<FIRST_MSG_ADD_DIRECTORY<< "\n";
	for (unsigned int i=0;i<vec.size();i++)
		cout<<vec[vec.size()-1-i]<< "\n";
	return true;
}
