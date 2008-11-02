#ifndef ADDDIRECTORY_H_
#define ADDDIRECTORY_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Agrega un directorio de imagenes al ocultador.
 */
class AddDirectory : public Command
{

private:
	static const int numParams = 2;

public:
	AddDirectory(std::string cmd);
	AddDirectory();
	virtual ~AddDirectory();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_ADD_DIRECTORY;}
};

#endif /*ADDDIRECTORY_H_*/
