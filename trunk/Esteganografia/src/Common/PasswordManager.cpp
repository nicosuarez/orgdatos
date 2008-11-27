#include "PasswordManager.h"
#include <string>
#include <fstream>
#include "Date.h"
#include "../DataAccess/Files/ExtensibleRelativeFile.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "Exception/eBrokenProgram.h"
#include "MessageManager.h"
#include "Resource.h"
#include "EncriptationManager.h"
#include "CompressionManager.h"

using std::cout;

PasswordManager::PasswordManager() {
}

PasswordManager::~PasswordManager() {
}

bool PasswordManager::ValidatePassword(){
	bool ans=false;
	std::ifstream fpImg(PATH_IMG_FILE,std::ios::in);
	if(!fpImg.good())
		return false; //Si no existe devuelve false
	fpImg.close();
	Date datePass=Date::getDate(PATH_PASS_FILE);
	OrgExtensibleRelative fImg(PATH_IMG_FILE, ImgRegistry::Create);
	//fImg.Open(ExtensibleRelativeFile::READ);
	ImgRegistry* reg=(ImgRegistry*)fImg.GetRegistry(1);
	//fImg.close();
	if (reg->GetDate()==datePass){
		delete reg;
		ans=true;
	}else{
		delete reg;
		throw eBrokenProgram(MSGCORRUPT_PASS);
	}
	return ans;
}

void PasswordManager::stringToMsg(string pass,Message msg){
	ofstream fp(msg.GetFilePath(),ios::out|ios::trunc);
	fp.write(pass.c_str(),sizeof(char)*pass.length());
	fp.close();
}

bool PasswordManager::IsCorrectPass(const std::string& st){
	Message message(PATH_PASS_FILE);
	Message truePass=PasswordManager::Extract(message);
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
	if( remove( truePass.GetFilePath()) != 0 )
		    perror( "Error deleting file" );
	return (!strcmp(pass,st.c_str()));
}

Message PasswordManager::Extract(const Message& msg,const Message& msgTarget){
	Message m1=EncriptationManager::Decrypt(msg);
	CompressionManager::Decompress(m1,msgTarget);
	return msgTarget;
}

void PasswordManager::Hide(const Message& msg,const Message& msgTarget){
	Message m1=CompressionManager::Compress(msg);
	EncriptationManager::Encrypt(m1,msgTarget);
}

void PasswordManager::CreatePass(const Message& msg,short mode){
	PasswordManager::Hide(msg,Message(PATH_PASS_FILE));
	ImgRegistry* reg;
	OrgExtensibleRelative fImg(PATH_IMG_FILE, ImgRegistry::Create);
	Date datePass=Date::getDate(PATH_PASS_FILE);
	if (mode==PasswordManager::CHANGE){
		reg=dynamic_cast<ImgRegistry*>(fImg.GetRegistry(1));
		reg->SetDate(datePass);
		reg->SetIDImagePath(0);
		fImg.UpdateRegistry(*reg);
	}else{
		reg=new ImgRegistry;
		reg->SetDate(datePass);
		reg->SetIDImagePath(0);
		fImg.WriteRegistry(*reg);
	}
	delete reg;
}

bool PasswordManager::ChangePass(const string& oldPass,const string& newPass){
	bool ans=false;
	bool isOk=IsCorrectPass(oldPass);
	if (isOk){
		Message msg(PATH_PASS_TEMP);
		stringToMsg(newPass,msg);
		CreatePass(msg,PasswordManager::CHANGE);
		msg.Delete();
		ans=true;
	}
	return ans;
}
