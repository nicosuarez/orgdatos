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
	return true;
}
