#include "RemoveDirectory.h"

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
	return true;
}
