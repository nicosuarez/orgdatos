#ifndef HELP_H_
#define HELP_H_

#include "CommandFactory.h"

/**
 * Muestra la ayuda para todos los comandos disponibles.
 */
class Help : public Command
{
public:
	Help(std::string cmd);
	Help();
	virtual ~Help();

	bool Validate(std::string cmd);
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_ADD_DIRECTORY;}
};

#endif /*HELP_H_*/
