#include "ChangePassword.h"

using namespace std;

ChangePassword::ChangePassword(string cmd) : Command(cmd)
{

}

ChangePassword::ChangePassword() : Command(" ")
{

}

ChangePassword::~ChangePassword()
{
}

/**
 * Muestra la ayuda del comando.
 */
void ChangePassword::ShowHelpCommand()
{
	cout << HLP_CHANGE_PASSWORD<< "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool ChangePassword::InternalProcess(tVecStr params)
{
	return true;
}
