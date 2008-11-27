#ifndef SHOWFILES_H_
#define SHOWFILES_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Muestra el nombre de los archivos ocultos.
 */
class ShowFiles : public Command
{
private:
	static const int numParams = 1;
	
public:
	ShowFiles(std::string cmd);
	ShowFiles();
	virtual ~ShowFiles();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_SHOW_FILES;}
};

#endif /*SHOWFILES_H_*/
