#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

#include "AddDirectory.h"
#include "Help.h"
#include "StrToken.h"

typedef std::vector<Command*> tVecCmd;

class CommandFactory
{
public:
	static bool IsQuitCommand(string cmd);
	static bool IsAddDirectoryCommand(string cmd);
	static bool IsRemoveDirectoryCommand(string cmd);
	static bool IsRemoveFileCommand(string cmd);
	static bool IsAddFileCommand(string cmd);
	static bool IsGetFileCommand(string cmd);
	static bool IsShowFilesCommand(string cmd);
	static bool IsShowDirectoriesCommand(string cmd);
	static bool IsChangePasswordCommand(string cmd);
	static bool IsHelpCommand(string cmd);
	static Command* CreateCommand(string cmd);
	static void ShowCommandNotExistMsg();
	static tVecCmd GetAllCommandsList();
};

#endif /*COMMANDFACTORY_H_*/
