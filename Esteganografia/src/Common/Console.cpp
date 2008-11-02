///////////////////////////////////////////////////////////
//  Console.cpp
//  Implementation of the Class Space
//  Created on:      30-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "CommandFactory.h"
#include "Console.h"

using namespace std;

int Console::Run(int argc,char* argv[])
{
	string cmd;
	
	ShowInitialMessage();
	
	while(!CommandFactory::IsQuitCommand(cmd))
	{
		ShowPrompt();
		getline(cin,cmd);
		Command* command = CommandFactory::CreateCommand(cmd);
		if(command != NULL)
		{
			command->Run(cmd);
			delete command;
		}
	}
	
	return 0;
}

void Console::ShowInitialMessage()
{
	cout << MSG_INITIAL_PROGRAM << "\n";
}

void Console::ShowPrompt()
{
	cout << "\n" << LBL_PROMT;
}



