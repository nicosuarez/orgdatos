#include "PasswordManager.h"
#include <string>
#include <fstream>
#include "Date.h"
#include "../DataAccess/Files/ExtensibleRelativeFile.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "Exception/eBrokenProgram.h"
#include "MessageManager.h"
#include "Resource.h"
#include "Constant.h"

using namespace std;

PasswordManager::PasswordManager() {
	// TODO Auto-generated constructor stub

}

PasswordManager::~PasswordManager() {
	// TODO Auto-generated destructor stub
}

bool PasswordManager::ValidatePassword(){
	bool ans=false;
	std::ifstream fpImg(PATH_IMG_FILE,std::ios::in);
	if(!fpImg.good())
		return false; //Si no existe devuelve false
	fpImg.close();
	Date datePass=Date::getDate(PATH_PASS_FILE);
	ExtensibleRelativeFile fImg(PATH_IMG_FILE, ImgRegistry::RegCreate);
	fImg.Open(ExtensibleRelativeFile::READ);
	ImgRegistry* reg=(ImgRegistry*)fImg.Read(1);
	if (reg->getDate()==datePass){
		delete reg;
		ans=true;
	}else{
		delete reg;
		throw eBrokenProgram(MSGCORRUPT_PASS);
	}
	return ans;
}

void PasswordManager::InsertNewPassword(string pass,Message msg){
	ofstream fp(msg.GetFilePath(),ios::out|ios::trunc);
	fp.write(pass.c_str(),sizeof(char)*pass.length());
	fp.close();
}

bool PasswordManager::IsCorrectPass(const std::string& st){
	Message message(PATH_PASS_FILE);
	Message truePass=MessageManager::GetInstance()->Extract(message);
	ifstream fp(truePass.GetFilePath(), ios::in);
	unsigned long begin, end, size;
	begin = fp.tellg();
	fp.seekg(0, ios::end);
	end = fp.tellg();
	size = end - begin;
	fp.seekg(0, ios::beg);
	char* pass=new char[size+1];
	fp.get(pass,sizeof(char)*(size+1));
	string aux=pass;
	pass[size]='\0';
	aux=pass;
	return (!strcmp(pass,st.c_str()));
}
