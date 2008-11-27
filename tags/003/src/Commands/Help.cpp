#include "Help.h"

Help::Help(string cmd) : Command(cmd)
{

}

Help::Help() : Command(" ")
{

}

Help::~Help()
{
}

/**
 * Muestra la ayuda del comando.
 */
void Help::ShowHelpCommand()
{
	cout << HLP_HELP << "\n";
}

/**
 * Valida el formato del comando.
 */
bool Help::Validate(string cmd)
{
	StrToken::toLowerString(cmd);
	tVecStr params = StrToken::getStrTokens(cmd," ");
	
	if(params.size() != 1)
	{
		this->ShowParamsErrMsg();
		return false;
	}
	return true;	
}

/**
 * Ejecuta el comando correspondiente.
 */
bool Help::InternalProcess(tVecStr params)
{
	tVecCmd cmdVec = CommandFactory::GetAllCommandsList();
	for(size_t i=0; i < cmdVec.size(); i++)
	{
		Command* cmd = cmdVec[i];
		cmd->ShowHelpCommand();		
		cout << endl;
		delete cmd;
	}
	
	return true;
}


