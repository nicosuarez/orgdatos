#ifndef SHOWDIRECTORIES_H_
#define SHOWDIRECTORIES_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Muestra la ruta de los directorios que contienen que se utilizan para ocultar
 * textos.
 */
class ShowDirectories : public Command
{
private:
	static const int numParams = 2;
	
public:
	ShowDirectories(std::string cmd);
	ShowDirectories();
	virtual ~ShowDirectories();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_SHOW_DIRECTORIES;}
};

#endif /*SHOWDIRECTORIES_H_*/
