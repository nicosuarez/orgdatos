#include "Command.h"

using std::cout;
using std::string;

Command::Command(string cmd){
	this->cmd = cmd;
}

Command::~Command(){

}

bool Command::InternalProcess(tVecStr params)
{
	return false;
}
 
void Command::ShowParamsErrMsg()
{
	cout << "\n" << ERR_PARAMS_SIZE_INCORRECT << "\n" << std::flush;
}

void Command::ShowHelpCommand()
{
	
}

/**
 * Valida el formato del comando.
 */
bool Command::Validate(string cmd)
{
	StrToken::toLowerString(cmd);
	tVecStr params = StrToken::getStrTokens(cmd," ");
	
	if(params.size() != this->GetNumParams())
	{
		this->ShowParamsErrMsg();
		return false;
	}
	return true;	
}

/**
 * Ejecuta el comando correspondiente.
 */
bool Command::Run(string cmd)
{
	if(Validate(cmd))
	{
		tVecStr params = StrToken::getStrTokens(cmd," ");
		return InternalProcess(params);
	}
	else
	{
		this->ShowHelpCommand();
		std::cout << "\n";
	}
	return false;
}

unsigned int Command::GetNumParams()
{
	return 0;
}
