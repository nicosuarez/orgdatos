#include "GetFile.h"
using std::string;

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
	std::cout << HLP_GET_FILE << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool GetFile::InternalProcess(tVecStr params)
{
	string nameMessage = string(params[1]);
	string pathMessage = string(params[2]);
	MessageManager *messageManager = MessageManager::GetInstance();
	try
	{
		std::cout << PROCESS_COMMAND;
		messageManager->Extract(nameMessage, pathMessage);
		std::cout << MSG_EXTARCT_SUCCESS;
	}
	catch(eFile &e){
		std::cout << EXC_EFILE << e.what() << "\n";
	}
	catch(eNotExist &e)
	{
		std::cout << e.what() << "\n"; 
	}
	return true;
}
