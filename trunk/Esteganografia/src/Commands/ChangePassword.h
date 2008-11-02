#ifndef CHANGEPASSWORD_H_
#define CHANGEPASSWORD_H_

#include "Command.h"
#include "../Steganographic/ImageFactory.h"
#include "../Common/ImageManager.h"
#include "../Common/FileSystem.h"

/**
 * Modifica el password de ingreso.
 */
class ChangePassword : public Command
{
private:
	static const int numParams = 2;
	
public:
	ChangePassword(std::string cmd);
	ChangePassword();
	virtual ~ChangePassword();

	unsigned int GetNumParams(){return numParams;};
	bool InternalProcess(tVecStr params);
	void ShowHelpCommand();
	
	static std::string GetName(){return CMD_CHANGE_PASSWORD;}
};

#endif /*CHANGEPASSWORD_H_*/
