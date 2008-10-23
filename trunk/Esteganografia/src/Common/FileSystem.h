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

using namespace std;

/**
 * Clase que maneja el FileSystems.
 */
class FileSystem
{
public:
	static vector<string> GetFiles(char* path);
};

#endif /*FILESYSTEM_H_*/
