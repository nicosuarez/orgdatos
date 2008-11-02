#ifndef REMOVEFILE_H_
#define REMOVEFILE_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Quita un archivo de texto del ocultador.
 */
class RemoveFile : public Command
{
private:
	static const int numParams = 2;
	
public:
	RemoveFile(std::string cmd);
	RemoveFile();
	virtual ~RemoveFile();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_REMOVE_FILE;}
};

#endif /*REMOVEFILE_H_*/
