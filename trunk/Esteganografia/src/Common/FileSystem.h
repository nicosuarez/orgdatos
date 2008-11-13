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
#include "Resource.h"
#include "Message.h"


typedef enum FSMode {File=0 , All=1, Dir=2 } FSMode;

/**
 * Clase que maneja el FileSystems.
 */
class FileSystem
{
public:
	static std::vector<std::string> GetFiles(const char* path, FSMode mode);
	 /**
	 * Devuelve true si la estructura es valida
	 */
	static bool IsValidStructure();

	/**
	 * Crea toda la estructura de archivo incluyendo el password (con el mensaje de paramtro)
	 * lanza ex de eFile
	 */
	static void CreateStruture(const Message& pass);

private:
	/**
	  * Crea el archivo de password
	  * Lanza ex de eFile
	*/
	static void CreatePass(const Message& msg);
};

#endif /*FILESYSTEM_H_*/
