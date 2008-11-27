#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <errno.h>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <string>
#include <vector>
#include "Message.h"
#include "Resource.h"

typedef enum FSMode {File=0 , Dir=1 ,All=3} FSMode;

typedef std::vector<std::string> tVecStr;
/**
 * Clase que maneja el FileSystems.
 */
class FileSystem
{
private:
		/* Returns true if the entity (file or directory) is hidden
		 * otherwise returns false. */
		static bool isHide (const char* );

	    /* Gets the extension from the file name (string). */
		static std::string getFileExt (const std::string& );

public:
	/* Returns true if the image extension is supported otherwise
	 * returns false. */
	static bool isASupportedImage (const std::string& );

	/* Returns a list of files or subdirectories from a path.
	 * returns false.
	 * FSMode: filter through file or directory */
	static tVecStr GetFiles(const char* path, FSMode mode);

	 /**
	 * Devuelve true si la estructura es valida
	 */
	static bool IsValidStructure();
	
	/**
	 * Crea toda la estructura de archivo incluyendo el password (con el mensaje de paramtro)
	 * lanza ex de eFile
	 */
	static void CreateStruture(const Message& pass);
	
	/*Devuelve true si existe el directorio pasado por parametro*/
	static bool ExistDirectory(const char *path);
	
	/*Verifica si el path completo es un directorio o una imagen*/
	static bool IsDirectory(const char *path);

};

#endif /*FILESYSTEM_H_*/
