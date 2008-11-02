#ifndef ADDDIRECTORY_H_
#define ADDDIRECTORY_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "ImageManager.h"
#include "FileSystem.h"

/**
 * Agrega un directorio de imagenes al ocultador.
 */
class AddDirectory : public Command
{
public:
	AddDirectory(std::string cmd);
	AddDirectory();
	virtual ~AddDirectory();

	bool Validate(std::string cmd);
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_ADD_DIRECTORY;}
};

#endif /*ADDDIRECTORY_H_*/
