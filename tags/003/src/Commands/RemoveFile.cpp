#include "RemoveFile.h"

RemoveFile::RemoveFile(string cmd) : Command(cmd)
{

}

RemoveFile::RemoveFile() : Command(" ")
{

}

RemoveFile::~RemoveFile()
{
}

/**
 * Muestra la ayuda del comando.
 */
void RemoveFile::ShowHelpCommand()
{
	cout << HLP_REMOVE_FILE << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool RemoveFile::InternalProcess(tVecStr params)
{
	std::string nameMessage = std::string(params[1]);
	MessageManager *messageManager = MessageManager::GetInstance();
	try
	{
		messageManager->DeleteMessage(nameMessage, true);
		cout <<  "\n" << MSG_DELETE_SUCCESS << endl;
	}
	catch(eFile &e)
	{
		cout <<  "\n" << EXC_EFILE << e.what() << "\n";
	}
	catch(eNotExist &e)
	{
		cout << "\n" << e.what() << "\n";
	}
	return true;
}
