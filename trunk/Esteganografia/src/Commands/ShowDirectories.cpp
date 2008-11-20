#include "ShowDirectories.h"

using namespace std;

ShowDirectories::ShowDirectories(string cmd) : Command(cmd)
{

}

ShowDirectories::ShowDirectories() : Command(" ")
{

}

ShowDirectories::~ShowDirectories()
{
}

/**
 * Muestra la ayuda del comando.
 */
void ShowDirectories::ShowHelpCommand()
{
	cout << HLP_SHOW_DIRECTORIES << "\n";
}

/**
 * Ejecuta el comando correspondiente.
 */
bool ShowDirectories::InternalProcess(tVecStr params)
{
	string path = params[1];
	ImageManager* iManager=ImageManager::GetInstance();
	tVecStr vec =iManager->GetAllDirectories();
	if (vec.size()!=0)
		cout<<FIRST_MSG_ADD_DIRECTORY<< "\n";
	for (unsigned int i=0;i<vec.size();i++)
	{
		cout<<vec[vec.size()-1-i]<< "\n";
	}
	vec.clear();
	return true;
}
