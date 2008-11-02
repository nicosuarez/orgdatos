#ifndef REMOVEDIRECTORY_H_
#define REMOVEDIRECTORY_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Quita un directorio de imagenes del ocultador.
 */
class RemoveDirectory : public Command
{
private:
	static const int numParams = 2;
	
public:
	RemoveDirectory(std::string cmd);
	RemoveDirectory();
	virtual ~RemoveDirectory();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_REMOVE_DIRECTORY;}
};

#endif /*REMOVEDIRECTORY_H_*/
