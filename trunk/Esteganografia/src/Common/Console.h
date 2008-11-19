#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <unistd.h>
#include "../Commands/CommandFactory.h"
#include <readline/readline.h>
#include <readline/history.h>

#include "Message.h"

/**
 * Clase que se encarga de correr el hilo principal
 **/
class Console
{
static const int cantIntentosPass = 3;

public:
	static int Run(int argc,char* argv[]);
	static bool InsertNewPassword(Message& msg);
private:
	//static bool ExistPassword();
	//static bool IsCorrectPass(const std::string& st);
	static pair<bool,tVecStr> ValidatePassword();
	static std::string GetInputPassword();
	static void ShowInitialMessage();
	static void ReadCommand(std::string& cmd);
	static char** AutoCompletion(const char * text, int start, int end);
	static char* Generator(const char* text, int state) ;
	static tVecStr GetAllCommands();
	static char * StrToChar (std::string str);
//	static void *Xmalloc (int);
	static const string temporaryFile;

};

#endif /*CONSOLE_H_*/
