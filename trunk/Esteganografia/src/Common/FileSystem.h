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

using namespace std;

typedef enum FSMode {File=0 , All=1, Dir=2 } FSMode;

/**
 * Clase que maneja el FileSystems.
 */
class FileSystem
{	
public:
	static vector<string> GetFiles(const char* path, FSMode mode);
};

#endif /*FILESYSTEM_H_*/
