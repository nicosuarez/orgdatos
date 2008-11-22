#include "FileSystem.h"
#include "Exception/eFile.h"
#include "Date.h"
#include "MessageManager.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "../DataAccess/Files/ExtensibleRelativeFile.h"
#include "Constant.h"
#include "PasswordManager.h"

using namespace std;

/* -------------------------------------------------------------------------- */

bool FileSystem::isHide (const char* hide)
{
	/* If the entity is hidden the firt char must be '.'. */
	return hide[0] == '.';
}

/* -------------------------------------------------------------------------- */

std::string FileSystem::getFileExt (const std::string& str)
{
   /* Searches '.' in a backward direction, and returns the position of
    * the last occurrence in the string str*/
   size_t i = str.rfind('.', str.length());

   if ( i != std::string::npos )
   /* The extension has been found it and returned. */
      return (str.substr(i+1, str.length() - i));
   return "";
}

/* -------------------------------------------------------------------------- */

bool FileSystem::isASupportedImage (const std::string& filename)
{
	std::vector <std::string> supported;

	/* The vector supported is loaded with possible extensions.*/
	supported.push_back (EXT_BMP);	supported.push_back(EXT_JPG);
	supported.push_back(EXT_JPEG);	supported.push_back(EXT_PNG);
	supported.push_back(EXT_GIF);
	std::string ext = "." + getFileExt (filename);
	unsigned int j = 0, size = supported.size();
	bool found = false;

	while ( (j < size) && (!found) )
	{
		if ( std::string::npos != ext.find( supported.at(j) , 0 ) )
			found = true;
		j++;
	}
	supported.clear();
	return found;
}

/* -------------------------------------------------------------------------- */

std::vector<std::string> FileSystem::GetFiles(const char* path, FSMode mode)
{
	 DIR *pdir;
	 struct dirent *pent;
	 struct stat stFileInfo;
	 char szFullName[256];
	 std::vector<std::string> fileList, subfileList;

	 pdir = opendir(path);
	 if (!pdir)
	 {
		 std::cerr << ERR_PATH_NOT_EXIST << "\"" << path << "\"" << "\n" << std::flush;
		 return fileList;
	 }
	 errno = 0;
	 while ( ( pent = readdir (pdir) ) )
	 {
		  sprintf(szFullName, "%s/%s", path, pent->d_name);

		  if (lstat(szFullName, &stFileInfo) < 0)
			  perror ( szFullName );

		  /* The file or directory is not hidden. */
		  if ( !isHide(pent->d_name) )
		  {
		  	if ( S_ISREG(stFileInfo.st_mode) && ( mode == All || mode == File ) )
		  	{
		  	  /* The entity is a file. */
		  	  if ( isASupportedImage(pent->d_name) )
		  	  {
			   std::string file(pent->d_name);
			   fileList.push_back(file);
		  	  }
		  	}

		  	if ( S_ISDIR(stFileInfo.st_mode) && (mode == All || mode == Dir ) )
  		  	{
  		  	  /* The entity is a directory. */
  		  	  if ( ( strcmp (pent->d_name,".") != 0 ) &&
  		  	  ( strcmp (pent->d_name ,"..") != 0 )  )
  		  	  {
  		  	   if (mode == Dir)
  		  	   {
  		  	   	std::string file(pent->d_name);
	 		   	fileList.push_back(file);
  		  	   }

  			   subfileList = GetFiles (szFullName, mode);

  			   for (unsigned int i = 0; i < subfileList.size(); i++)
			   {
			   	 std::string str("/" + subfileList.at(i)), file(pent->d_name + str);
	 			 fileList.push_back(file);
		   	   }
			   subfileList.clear();

  		  	  }
  		  	}
		  }
	 }
	 if (errno){
		 std::cerr << ERR_FILE_ERROR << path << "\n" << std::flush;
		 closedir(pdir);
		 return fileList;
	 }
	 closedir(pdir);
	 return fileList;
}

/* -------------------------------------------------------------------------- */

bool FileSystem::IsValidStructure(){
	return true;
}

/* -------------------------------------------------------------------------- */

void FileSystem::CreateStruture(const Message& pass){
	ImgRegistry reg;
	ExtensibleRelativeFile fImg(PATH_IMG_FILE, ImgRegistry::RegCreate);
	fImg.Create(reg.GetSize());

	PasswordManager::CreatePass(pass,PasswordManager::NEW);
}
/* -------------------------------------------------------------------------- */


bool FileSystem:: ExistDirectory(const char *path)
{
	 DIR *pdir = opendir( path );
	 if (!pdir)
		 return false;
	 else
		 return true;
}
