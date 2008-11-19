#include "GetFile.h"

using namespace std;

GetFile::GetFile(string cmd) : Command(cmd)
{

}

GetFile::GetFile() : Command(" ")
{

}

GetFile::~GetFile()
{
}

/**
 * Muestra la ayuda del comando.
 */
void GetFile::ShowHelpCommand()
{
	cout << HLP_GET_FILE << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool GetFile::InternalProcess(tVecStr params)
{
	std::string pathMessage = std::string(params[2] + "/" + params[1]);
	MessageManager *messageManager = MessageManager::GetInstance();
	bool isOk=messageManager->Extract(pathMessage);
	if(!isOk)
		cout<<ERR_MSG_NOT_EXIST;
	return true;
}
