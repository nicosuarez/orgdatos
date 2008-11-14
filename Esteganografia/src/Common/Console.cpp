#include "Console.h"
#include "Date.h"
#include "Message.h"
#include "Constant.h"
#include <fstream.h>
#include "Exception/eBrokenProgram.h"
#include "MessageManager.h"
#include "../DataAccess/Files/ExtensibleRelativeFile.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


using namespace std;

const string Console::temporaryFile="../Files/temporaryFileConsole.txt";

int Console::Run(int argc,char* argv[])
{
	string cmd;
	if (ExistPassword()){
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
	}else{
		/*PEDIR PASS Y CREAR TODAS LAS ESTRUCTURAS*/
		Message pass;
		bool val=Console::InsertNewPassword(pass);
		if(val)
			FileSystem::CreateStruture(pass);
	}
	return 0;
}

/**
 * Devuelve true si ya se ha seteado un password
 * Si la el passesta corrompida tira excepcion
 */
bool Console::ExistPassword(){
	bool ans=false;
	std::ifstream fpImg(Constant::ImgFile.c_str(),std::ios::in);
	if(!fpImg.good())
		return false;
	fpImg.close();
	//Extraigo fecha
	struct tm* clock;				// create a time structure
	struct stat attrib;			// create a file attribute structure
	stat(Constant::PassFile.c_str(), &attrib);		// get the attributes of afile.txt
	clock = gmtime(&(attrib.st_mtime));	// Get the last modified time and put it into the time structure
	Date datePass(clock->tm_year,clock->tm_mon,clock->tm_mday,clock->tm_hour,clock->tm_min,clock->tm_sec);
	//COMPARAR!! la fecha con el archivo
	ExtensibleRelativeFile fImg(Constant::ImgFile.c_str(), ImgRegistry::RegCreate);
	fImg.Open(ExtensibleRelativeFile::READ);
	ImgRegistry* reg=(ImgRegistry*)fImg.Read(1);
	if (reg->getDate()==datePass)
		ans=true;
	delete reg;
	return ans;
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
 * Devuelve si el pass ingresado(st) es igual al original
 */
bool Console::IsCorrectPass(const string& st){
	Message message(Constant::PassFile.c_str());
	Message truePass=MessageManager::Extract(message);
	ifstream fp(truePass.GetFilePath(), ios::in);
	unsigned long begin, end, size;
	begin = fp.tellg();
	fp.seekg(0, ios::end);
	end = fp.tellg();
	size = end - begin;
	fp.seekg(0, ios::beg);
	char* pass=new char[size+1];
	fp.get(pass,sizeof(char)*(size+1));
	string aux=pass;
	pass[size]='\0';
	aux=pass;
	return (!strcmp(pass,st.c_str()));
}


/**
 * Pide el nuevo password y su confirmacion. Devuelve un true si fue ingresado correctamente
 * y en ese caso lo guarda en un mensaje
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
	msg.SetFilePath(Console::temporaryFile.c_str());
	ofstream fp(msg.GetFilePath(),ios::out|ios::trunc);
	fp.write(pass1.c_str(),sizeof(char)*pass1.length());
	fp.close();
	return true;
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
		if (Console::IsCorrectPass(pass))
			esValido=true;
		else
			cout << ERR_INCORRECT_PASSWORD << "\n" << flush;
		intentos++;
	}
	return esValido;
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


