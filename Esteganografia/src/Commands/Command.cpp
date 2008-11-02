///////////////////////////////////////////////////////////
//  Command.cpp
//  Implementation of the Class Command
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Command.h"

using namespace std;

Command::Command(string cmd){

}

Command::~Command(){

}

bool Command::InternalProcess(tVecStr params)
{
	return false;
}
 
void Command::ShowParamsErrMsg()
{
	cout << ERR_PARAMS_SIZE_INCORRECT << "\n" << flush;
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
		StrToken::toLowerString(cmd);
		tVecStr params = StrToken::getStrTokens(cmd," ");
		return InternalProcess(params);
	}
	else
	{
		this->ShowHelpCommand();
	}
	return false;
}

unsigned int Command::GetNumParams()
{
	return 0;
}
