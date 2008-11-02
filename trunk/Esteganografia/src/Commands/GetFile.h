#ifndef GETFILE_H_
#define GETFILE_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Obtiene el mensaje oculto.
 */
class GetFile : public Command
{
private:
	static const int numParams = 2;
	
public:
	GetFile(std::string cmd);
	GetFile();
	virtual ~GetFile();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_GET_FILE;}
};

#endif /*GETFILE_H_*/
