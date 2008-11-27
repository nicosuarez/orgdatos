#include "AddFile.h"

using std::cout;

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
	try
	{
		std::cout << "\n" << PROCESS_COMMAND;
		if( FileSystem::IsDirectory(pathMessage.c_str()) )
			throw eNotExist(MSG_NOT_MSG);
		messageManager->Hide(pathMessage);
		std::cout << MSG_HIDE_SUCCESS;
	}
	catch(eFile &e){
		cout << "\n" << EXC_EFILE << e.what() << "\n\n";
	}
	catch(exception &e){
		cout << e.what() << "\n\n";
	}
	return true;
}
