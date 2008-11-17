#include "CommandFactory.h"

using namespace std;

bool CommandFactory::IsQuitCommand(string cmd)
{
	StrToken::toLowerString(cmd);
	tVecStr params = StrToken::getStrTokens(cmd," ");

	if(params.size()==1)
	{	
		if(params[0] == CMD_QUIT)
			return true;
	}
	return false;
}

bool CommandFactory::IsAddDirectoryCommand(string cmd)
{
	return (cmd == CMD_ADD_DIRECTORY);
}

bool CommandFactory::IsHelpCommand(string cmd)
{
	return (cmd == CMD_HELP);
}

bool CommandFactory::IsRemoveDirectoryCommand(string cmd)
{
	return (cmd == CMD_REMOVE_DIRECTORY);
}

bool CommandFactory::IsRemoveFileCommand(string cmd)
{
	return (cmd == CMD_REMOVE_FILE);
}

bool CommandFactory::IsAddFileCommand(string cmd)
{
	return (cmd == CMD_ADD_FILE);
}

bool CommandFactory::IsGetFileCommand(string cmd)
{
	return (cmd == CMD_GET_FILE);
}

bool CommandFactory::IsShowFilesCommand(string cmd)
{
	return (cmd == CMD_SHOW_FILES);
}

bool CommandFactory::IsShowDirectoriesCommand(string cmd)
{
	return (cmd == CMD_SHOW_DIRECTORIES);
}

bool CommandFactory::IsChangePasswordCommand(string cmd)
{
	return (cmd == CMD_SHOW_DIRECTORIES);
}

void CommandFactory::ShowCommandNotExistMsg()
{
	cout << ERR_COMMAND_NOT_EXIST << "\n";
}

Command* CommandFactory::CreateCommand(string cmd)
{
	string cmdName = EMPTY;
	tVecStr params = StrToken::getStrTokens(cmd," ");
	if(params.size() > 0)
	{
		cmdName = params[0];
		StrToken::toLowerString(cmdName);
	}
	
	if (CommandFactory::IsAddDirectoryCommand(cmdName))
		return new AddDirectory(cmd);
	else if (CommandFactory::IsRemoveDirectoryCommand(cmdName))
		return new RemoveDirectory(cmd);
	else if (CommandFactory::IsHelpCommand(cmdName))
		return new Help(cmd); // new RemoveDirectory(cmd);
	else if (CommandFactory::IsRemoveFileCommand(cmdName))
		return new RemoveFile(cmd);
	else if (CommandFactory::IsAddFileCommand(cmdName))
		return new AddFile(cmd);
	else if (CommandFactory::IsGetFileCommand(cmdName))
		return new GetFile(cmd);
	else if (CommandFactory::IsShowFilesCommand(cmdName))
		return new ShowFiles(cmd);
	else if (CommandFactory::IsShowDirectoriesCommand(cmdName))
		return new ShowDirectories(cmd);
	else if (CommandFactory::IsChangePasswordCommand(cmdName))
		return new ChangePassword(cmd);
	else if(CommandFactory::IsQuitCommand(cmdName))
		return NULL;
	else
		ShowCommandNotExistMsg();
		
	return NULL;
}

tVecCmd CommandFactory::GetAllCommandsList()
{
	vector<Command*> cmdVec;
	cmdVec.push_back(new AddDirectory());
	cmdVec.push_back(new Help());
	cmdVec.push_back(new RemoveDirectory());
	cmdVec.push_back(new RemoveFile());
	cmdVec.push_back(new AddFile());
	cmdVec.push_back(new GetFile());
	cmdVec.push_back(new ShowFiles());
	cmdVec.push_back(new ShowDirectories());
	cmdVec.push_back(new ChangePassword());
	return cmdVec;
}
