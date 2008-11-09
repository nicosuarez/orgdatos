///////////////////////////////////////////////////////////
//  Console.cpp
//  Implementation of the Class Space
//  Created on:      30-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Console.h"

using namespace std;

int Console::Run(int argc,char* argv[])
{
	string cmd;
	if(ValidatePassword())
	{
		ShowInitialMessage();
		while(!CommandFactory::IsQuitCommand(cmd))
		{
			ReadCommand(cmd);
			Command* command = CommandFactory::CreateCommand(cmd);
			if(command != NULL)
			{
				command->Run(cmd);
				delete command;
			}
		}
	}
	return 0;
}

/**
 * Obtiene una lista de todos los cmd disponibles en la consola.
 */
tVecStr Console::GetAllCommands()
{
	tVecStr vecCmd;
	vecCmd.push_back(CMD_QUIT);
	vecCmd.push_back(CMD_ADD_DIRECTORY);
	vecCmd.push_back(CMD_REMOVE_DIRECTORY);
	vecCmd.push_back(CMD_HELP);
	vecCmd.push_back(CMD_ADD_FILE);
	vecCmd.push_back(CMD_REMOVE_FILE);
	vecCmd.push_back(CMD_SHOW_DIRECTORIES);
	vecCmd.push_back(CMD_SHOW_FILES);
	vecCmd.push_back(CMD_CHANGE_PASSWORD);
	return vecCmd;
}

/**
 * Se valida el pass ingresado, tiene tantos intentos como la variables
 * cantIntentosPass indique.
 */
bool Console::ValidatePassword()
{
	bool esValido=false;
	int intentos=0;
	while(!esValido && intentos < cantIntentosPass)
	{
		string pass;
		cout << MSG_INPUT_PASSWORD << "(" << (intentos+1) << "/"<< cantIntentosPass << ")\n" << flush;
		pass = GetInputPassword();
		//TODO: LLAMAR A LA VALIDACION POSTA.
		if(pass == "12")
			esValido=true;

		if(!esValido)
			cout << ERR_INCORRECT_PASSWORD << "\n" << flush;

		intentos++;
	}
	return esValido;
}

/**
 * Obtiene el password de manera oculta, no se muestra mientras se
 * escribe por cuestiones de seguridad.
 */
string Console::GetInputPassword()
{
	string password;
	password = getpass(LBL_PASS);
	return password;
}

void Console::ShowInitialMessage()
{
	cout << MSG_INITIAL_PROGRAM << "\n";
}

/**
 * Se lee el comando ingresado. Guardando la lista de comandos en el
 * historial (Menos el password que se lo elimina del historial por seguridad)
 */
void Console::ReadCommand(string& cmd)
{
	rl_attempted_completion_function = AutoCompletion;
	rl_bind_key('\t',rl_complete);
	cmd = readline(LBL_PROMT);
	if(!cmd.empty())
		add_history(cmd.c_str());
}

/**
 * Se permite el autocompletados de comandos mediante la tecla tab.
 */
char** Console::AutoCompletion( const char * text , int start,  int end)
{
     char **matches;
     matches = (char **)NULL;

     if (start == 0)
         matches = rl_completion_matches ((char*)text, & Generator);
     else
         rl_bind_key('\t',rl_abort);

     return (matches);
}

/**
 * Busca en todos los comandos posibles para autocomplar el texto.
 */
char* Console::Generator(const char* text, int state)
{
	 //Obtengo todos los comandos posibles.
	 tVecStr cmd = GetAllCommands();
     static int len;
     static size_t index;
     string empty = EMPTY;
     string name = EMPTY;

     if (!state) {
    	 index = 0;
         len = strlen (text);
     }

     while(index < cmd.size())
     {
    	 name = cmd[index];
    	 if(name.compare(0,len,text)==0)
    	 {
    		 index++;
    		 return StrToChar(name);
    	 }
    	 index++;
     }
     //Si ya verifico todos los comandos y no encontro nada
     //retorno null.
     return ((char *)NULL);
 }

/**
 * Convierte un string a char*
 */
char * Console::StrToChar (string s)
{
   char *r = (char*) malloc(s.length() + 1);
   strcpy (r, s.c_str());
   return (r);
 }


