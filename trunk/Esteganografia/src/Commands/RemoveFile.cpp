#include "RemoveFile.h"

using namespace std;

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
	return true;
}
