#include "ChangePassword.h"
#include "../Common/Console.h"
#include "../Common/PasswordManager.h"



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
	string oldPass=params[1];
	string newPass=params[2];
	bool isOk=PasswordManager::ChangePass(oldPass,newPass);
	cout<<endl;
	if (!isOk)
		cout<<CHANGE_PASS_WRONG_PASS<< "\n\n";
	else
		cout<<CHANGE_PASS_ACCEPTED<< "\n\n";
	return true;
}
