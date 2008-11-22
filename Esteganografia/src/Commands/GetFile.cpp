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
	std::string nameMessage = std::string(params[1]);
	std::string pathMessage = std::string(params[2]);
	MessageManager *messageManager = MessageManager::GetInstance();
	try{
		bool isOk=messageManager->Extract(nameMessage, pathMessage);
		if(!isOk)
			cout<<ERR_MSG_NOT_EXIST;
		else
			cout<< MSG_EXTARCT_SUCCESS;
	}catch(eFile e){
		cout<< EXC_EFILE<<e.what() << "\n";
	}
	return true;
}
