#include "AddFile.h"

using namespace std;

AddFile::AddFile(string cmd) : Command(cmd)
{

}

AddFile::AddFile() : Command(" ")
{

}

AddFile::~AddFile()
{
}

/**
 * Muestra la ayuda del comando.
 */
void AddFile::ShowHelpCommand()
{
	cout << HLP_ADD_FILE << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool AddFile::InternalProcess(tVecStr params)
{
	std::string pathMessage = params[1];
	MessageManager *messageManager = MessageManager::GetInstance();
	try{
		messageManager->Hide(pathMessage);
	}catch(eFile e){
		cout<< EXC_EFILE<<e.what() << "\n";
	}
	return true;
}
