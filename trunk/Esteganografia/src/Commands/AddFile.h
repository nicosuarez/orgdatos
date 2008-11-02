#ifndef ADDFILE_H_
#define ADDFILE_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Agrega un mensaje ocultandolo.
 */
class AddFile : public Command
{
private:
	static const int numParams = 2;
	
public:
	AddFile(std::string cmd);
	AddFile();
	virtual ~AddFile();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_ADD_FILE;}
};

#endif /*ADDFILE_H_*/
