#include "AddDirectory.h"
#include "../Common/ImageManager.h"

using namespace std;

AddDirectory::AddDirectory(string cmd) : Command(cmd)
{

}

AddDirectory::AddDirectory() : Command(" ")
{

}

AddDirectory::~AddDirectory()
{
}

/**
 * Muestra la ayuda del comando.
 */
void AddDirectory::ShowHelpCommand()
{
	cout << HLP_ADD_DIRECTORY << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool AddDirectory::InternalProcess(tVecStr params)
{
	string path = params[1];
	tVecStr fileList = FileSystem::GetFiles(path.c_str(), File);
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
			ImageManager* iManager=ImageManager::GetInstance();
			iManager->AddDirectory(path.c_str());
			//ID_type id=iManager->AddImage(image);
		}

		fullPath = dirPath;
	}
	return true;
}
