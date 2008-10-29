///////////////////////////////////////////////////////////
//  Commands.cpp
//  Implementation of the Class Commands
//  Created on:      13-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Commands.h"

using namespace std;

Commands::Commands(){

}



Commands::~Commands(){

}


/**
 * Agrega un directorio de im�genes al ocultador.
 */
void Commands::AddDirectory(const char* path)
{
	vector<string> fileList = FileSystem::GetFiles(path, File);
	string dirPath(path);
	string fullPath(path);
	Image* image = NULL;
	
	for(size_t i=0; i < fileList.size(); i++)
	{
		cout << fileList[i] << "\n";
		fullPath.append(fileList[i]);
		cout << fullPath << "\n";
		if(ImageFactory::SupportedFormats(fullPath.c_str()))
		{
			image = ImageFactory::GetImage(fullPath.c_str());
			if(image != NULL)
			{
				image->Load();
			}
		}
		
		fullPath = dirPath;
	}
	
	
	
}


/**
 * Agrega un mensaje ocultandolo.
 */
void Commands::AddFile(const char* filePath){

}


/**
 * Modifica el password de ingreso.
 */
void Commands::ChangePassword(string newPass, string oldPass){

}


/**
 * Obtiene el mensaje oculto.
 */
void Commands::GetFile(const char* outFile, const char* filePath){

}


/**
 * Sale de la consola.
 */
void Commands::Quit(){

}


/**
 * Quita un directorio de im�genes del ocultador.
 */
void Commands::RemoveDirectory(const char* path){

}


/**
 * Quita un archivo de texto del ocultador.
 */
void Commands::RemoveFile(const char* path){

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
