#ifndef HELP_H_
#define HELP_H_

#include "CommandFactory.h"

/**
 * Muestra la ayuda para todos los comandos disponibles.
 */
class Help : public Command
{
private:
	static const int numParams = 1;
	
public:
	Help(std::string cmd);
	Help();
	virtual ~Help();

	unsigned int GetNumParams(){return numParams;};
	bool Validate(std::string cmd);
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_HELP;}
};

#endif /*HELP_H_*/
