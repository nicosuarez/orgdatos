#include "ShowDirectories.h"

using namespace std;

ShowDirectories::ShowDirectories(string cmd) : Command(cmd)
{

}

ShowDirectories::ShowDirectories() : Command(" ")
{

}

ShowDirectories::~ShowDirectories()
{
}

/**
 * Muestra la ayuda del comando.
 */
void ShowDirectories::ShowHelpCommand()
{
	cout << HLP_SHOW_DIRECTORIES << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool ShowDirectories::InternalProcess(tVecStr params)
{
	return true;
}
