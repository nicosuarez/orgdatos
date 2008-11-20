#include "Console.h"
#include "Date.h"
#include "Message.h"
#include "Constant.h"
#include <fstream.h>
#include "Exception/eBrokenProgram.h"
#include "../DataAccess/Files/ExtensibleRelativeFile.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "PasswordManager.h"
#include "IntrudersManager.h"

using namespace std;

int Console::Run(int argc,char* argv[])
{
	bool isUser=false;
	string cmd;
	if (PasswordManager::ValidatePassword()){
		pair<bool, tVecStr> valPass=ValidatePassword();
		if(valPass.first)
			isUser=true;
		else
			IntrudersManager::writeIntruder(valPass.second);
	}else{
		/*PEDIR PASS Y CREAR TODAS LAS ESTRUCTURAS*/
		Message pass;
		bool isOk=Console::InsertNewPassword(pass);
		if(isOk){
			FileSystem::CreateStruture(pass);
			isUser=true;
		}
		pass.Delete();
	}
	if (isUser){
		ShowInitialMessage();
		if (IntrudersManager::ExistNewIntruder() ){
			Console::ShowIntruderMessage();
		}
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
 * Muestra todos los intrusos que intentaron entrar y sus passwords
 */
void Console::ShowIntruderMessage(){
	tVecinstrud vecIntr=IntrudersManager::getIntruders();
	cout << MSG_INTRUDERS1 <<vecIntr.size();
	if (vecIntr.size()==1)
		cout<<MSG_INTRUDERS2<< "\n";
	else
		cout<<MSG_INTRUDERS3<< "\n";
	for (unsigned int i=0; i<vecIntr.size();i++)
		vecIntr[i].toOstream();
	cout<< "\n";
}

/**
 * Pide el nuevo password y su confirmacion. Devuelve un true si fue ingresado correctamente
 * y en ese caso lo guarda en msg
 */
bool Console::InsertNewPassword(Message& msg){
	bool esValido=false;
	int intentos=0;
	string pass1;
	string pass2;
	while(!esValido && intentos < cantIntentosPass)
	{
		cout << MSG_CREATE_PASSWORD << "(" << (intentos+1) << "/"<< cantIntentosPass << ")\n" << flush;
		pass1 = GetInputPassword();

		cout << MSG_COMFIRM_PASSWORD << "(" << (intentos+1) << "/"<< cantIntentosPass << ")\n" << flush;
		pass2 = GetInputPassword();

		if (!strcmp(pass1.c_str(),pass2.c_str()))
			esValido=true;
		else
			cout << ERR_SAME_PASSWORD << "\n" << flush;
		intentos++;
	}
	if (!esValido)
		return false;
	msg.SetFilePath(CONSOLE_TEMPORARY_FILE);
	PasswordManager::stringToMsg(pass1,msg);
	return true;
}

/**
 * Se valida el pass ingresado, tiene tantos intentos como la variables
 * cantIntentosPass indique.
 * Devuel si true si ingreso el pass correcto sino false y ademas los intentos hechos
 */
pair<bool,tVecStr> Console::ValidatePassword()
{
	pair<bool,tVecStr> ans;
	ans.first=false;
	int intentos=0;
	while(!ans.first && intentos < cantIntentosPass)
	{
		string pass;
		cout << MSG_INPUT_PASSWORD << "(" << (intentos+1) << "/"<< cantIntentosPass << ")\n" << flush;
		pass = GetInputPassword();

		//TODO: LLAMAR A LA VALIDACION POSTA.
		if (PasswordManager::IsCorrectPass(pass))
			ans.first=true;
		else{
			cout << ERR_INCORRECT_PASSWORD << "\n" << flush;
			(ans.second).push_back(pass);
		}
		intentos++;
	}
	return ans;
}


/**
 * Obtiene el password de manera oculta, no se muestra mientras se
 * escribe por cuestiones de seguridad.
 */
string Console::GetInputPassword(){
	string password;
	password = getpass(LBL_PASS);
	return password;
}

void Console::ShowInitialMessage(){
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


