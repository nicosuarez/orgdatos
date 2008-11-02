///////////////////////////////////////////////////////////
//  Commands.h
//  Implementation of the Class Commands
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include <string>
#include <vector>
#include "StrToken.h"
#include "Resource.h"

/**
 * Clase que implementa todos los comandos que se pueden ejecutar en el programa.
 */
class Command
{
protected:
	string cmd;
	
public:
	Command(std::string cmd);
	virtual ~Command();

	virtual bool Validate(std::string cmd);
	virtual bool Run(std::string cmd);
	virtual bool InternalProcess(tVecStr params);
	void ShowParamsErrMsg();
	virtual void ShowHelpCommand();	

};
#endif // !defined(EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_)
