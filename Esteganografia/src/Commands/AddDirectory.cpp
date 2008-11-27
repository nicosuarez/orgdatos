#include "AddDirectory.h"
#include "../Common/ImageManager.h"
#include "../Common/Exception/eNotExist.h"

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
	try{
		tVecStr vec =iManager->AddDirectory(path.c_str());
		cout<<FIRST_MSG_ADD_DIRECTORY<< "\n";
		for (unsigned int i=0;i<vec.size();i++)
		{
			cout<< CIRCLE << "\t" << vec[vec.size()-1-i]<< "\n";
		}
	}catch(eNotExist e){
		cout<<e.what()<< "\n";
	}	
	return true;
}
