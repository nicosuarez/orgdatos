///////////////////////////////////////////////////////////
//  Command.cpp
//  Implementation of the Class Command
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Command.h"

using namespace std;

Command::Command(string cmd){

}

Command::~Command(){

}

bool Command::InternalProcess(tVecStr params)
{
	return false;
}
 
void Command::ShowParamsErrMsg()
{
	cout << ERR_PARAMS_SIZE_INCORRECT << "\n" << flush;
}

void Command::ShowHelpCommand()
{
	
}

/**
 * Valida el formato del comando.
 */
bool Command::Validate(string cmd)
{
	return false;
}

/**
 * Ejecuta el comando correspondiente.
 */
bool Command::Run(string cmd)
{
	if(Validate(cmd))
	{
		StrToken::toLowerString(cmd);
		tVecStr params = StrToken::getStrTokens(cmd," ");
		return InternalProcess(params);
	}
	else
	{
		this->ShowHelpCommand();
	}
	return false;
}

//
///**
// * Agrega un mensaje ocultandolo.
// */
//void Command::AddFile(const char* filePath){
//
//}
//
//
///**
// * Modifica el password de ingreso.
// */
//void Command::ChangePassword(string newPass, string oldPass){
//
//}
//
//
///**
// * Obtiene el mensaje oculto.
// */
//void Command::GetFile(const char* outFile, const char* filePath){
//
//}
//
//
///**
// * Sale de la consola.
// */
//void Command::Quit(){
//
//}
//
//
///**
// * Quita un directorio de im�genes del ocultador.
// */
//void Command::RemoveDirectory(const char* path){
//
//}
//
//
///**
// * Quita un archivo de texto del ocultador.
// */
//void Command::RemoveFile(const char* path){
//
//}
//
//
///**
// * Muestra la ruta de los directorios que contienen que se utilizan para ocultar
// * textos.
// */
//void Command::ShowDirectories(){
//
//}
//
//
///**
// * Muestra el nombre de los archivos ocultos.
// */
//void Command::ShowFiles(){

//}
