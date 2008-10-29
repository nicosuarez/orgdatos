///////////////////////////////////////////////////////////
//  FileSystem.cpp
//  Implementation of the Class FileSystem
//  Created on:      22-Oct-2008 2:49:29 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "FileSystem.h"

using namespace std;

vector<string> FileSystem::GetFiles(const char* path, FSMode mode)
{
	 DIR *pdir;
	 struct dirent *pent;
	 struct stat stFileInfo;
	 char szFullName[256];
	 vector<string> fileList;

	 pdir=opendir(path);
	 if (!pdir)
	 {
		 cerr << "El directorio " << path << " no existe\n";
		 return fileList;
	 }
	 errno=0;
	 while ((pent=readdir(pdir)))
	 {
		  sprintf(szFullName, "%s/%s", path, pent->d_name);
		 
		  if (lstat(szFullName, &stFileInfo) < 0)
			  perror ( szFullName );
		
		  if (S_ISREG(stFileInfo.st_mode) && (mode==All || mode==File ))
		  {
			  string file(pent->d_name);
			  fileList.push_back(file);
		  }
		  
		  if (S_ISDIR(stFileInfo.st_mode) && (mode==All || mode==Dir ))
  		  {
  			  string file(pent->d_name);
  			  fileList.push_back(file);
  		  }
		  
		  if (S_ISLNK(stFileInfo.st_mode) && mode==All)
		  {
			  string file(pent->d_name);
			  fileList.push_back(file);
		  }
	 }
	 if (errno){
		 cerr <<  "Error al leer en el directorio: " << path << "\n";
		 closedir(pdir);
		 return fileList;
	 }
	 closedir(pdir);
	 return fileList;
}
