///////////////////////////////////////////////////////////
//  Commands.cpp
//  Implementation of the Class Commands
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Commands.h"


Commands::Commands(){

}



Commands::~Commands(){

}





/**
 * Agrega un directorio de im�genes al ocultador.
 */
void Commands::AddDirectory(string path){

}


/**
 * Agrega un mensaje ocultandolo.
 */
void Commands::AddFile(string filePath){

}


/**
 * Modifica el password de ingreso.
 */
void Commands::ChangePassword(string newPass, string oldPass){

}


/**
 * Obtiene el mensaje oculto.
 */
void Commands::GetFile(string outFile, string filePath){

}


/**
 * Sale de la consola.
 */
void Commands::Quit(){

}


/**
 * Quita un directorio de im�genes del ocultador.
 */
void Commands::RemoveDirectory(string path){

}


/**
 * Quita un archivo de texto del ocultador.
 */
void Commands::RemoveFile(string path){

}


/**
 * Muestra la ruta de los directorios que contienen que se utilizan para ocultar
 * textos.
 */
void Commands::ShowDirectories(){

}


/**
 * Muestra el nombre de los archivos ocultos.
 */
void Commands::ShowFiles(){

}
