#include "ShowFiles.h"

using namespace std;

ShowFiles::ShowFiles(string cmd) : Command(cmd)
{

}

ShowFiles::ShowFiles() : Command(" ")
{

}

ShowFiles::~ShowFiles()
{
}

/**
 * Muestra la ayuda del comando.
 */
void ShowFiles::ShowHelpCommand()
{
	cout << HLP_SHOW_FILES << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool ShowFiles::InternalProcess(tVecStr params)
{
	return true;
}
