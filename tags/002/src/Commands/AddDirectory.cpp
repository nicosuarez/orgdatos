#include "AddDirectory.h"
#include "../Common/ImageManager.h"
#include "../Common/Exception/eNotExist.h"

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
	try{
		tVecStr vec =iManager->AddDirectory(path.c_str());
		cout << FIRST_MSG_ADD_DIRECTORY << "\n";
		for (unsigned int i=0;i<vec.size();i++)
		{
			cout<< "\t" << CIRCLE << vec[vec.size()-1-i]<< "\n";
		}
		cout << "\n";
	}catch(eNotExist e){
		cout<<e.what()<< "\n\n";
	}	
	return true;
}
