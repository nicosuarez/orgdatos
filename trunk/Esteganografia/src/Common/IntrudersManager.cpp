/*
 * IntrudersManager.cpp
 *
 *  Created on: 19/11/2008
 *      Author: malcha
 */

#include "IntrudersManager.h"
#include "../DataAccess/Organizations/OrgText.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "PasswordManager.h"
#include "Message.h"
#include "Intruder.h"
#include "Constant.h"

IntrudersManager::IntrudersManager() {}

IntrudersManager::~IntrudersManager() {}

tVecinstrud IntrudersManager::getIntruders(){
	OrgText text(PATH_INTRUDER,FILE_INTRUDER);
	tVecinstrud intruders;
	OrgExtensibleRelative fImg(PATH_IMG_FILE, ImgRegistry::Create);
	ImgRegistry* reg=(ImgRegistry*)fImg.GetRegistry(1);
	for(unsigned int i=1;i<=reg->GetIDImagePath();i++){
		Intruder intrud;
		intrud.Deserialize( text.GetText(i) );
		intruders.push_back(intrud);
	}
	reg->SetIDImagePath(0);
	fImg.UpdateRegistry(*reg);
	text.Destroy();
	delete reg;
	return intruders;
}

bool IntrudersManager::ExistNewIntruder(){
	OrgExtensibleRelative fImg(PATH_IMG_FILE, ImgRegistry::Create);
	ImgRegistry* reg=(ImgRegistry*)fImg.GetRegistry(1);
	return ( (reg->GetIDImagePath())>0);
}

void IntrudersManager::writeIntruder(tVecStr vStr){
	OrgText text(PATH_INTRUDER,FILE_INTRUDER);
	string aux="basura";
	Message msg(PATH_PASS_TEMP);
	PasswordManager::stringToMsg(aux,msg);
	Date date=Date::getDate(msg.GetFilePath());
	msg.Delete();
	string toWrite=date.toString();
	for(unsigned int i=0;i<vStr.size();i++){
		toWrite=toWrite+vStr[i];
		toWrite=toWrite+"/";
	}
	text.WriteText(toWrite);
	OrgExtensibleRelative fImg(PATH_IMG_FILE, ImgRegistry::Create);
	ImgRegistry* reg=(ImgRegistry*)fImg.GetRegistry(1);
	reg->SetIDImagePath(reg->GetIDImagePath()+1);
	fImg.UpdateRegistry(*reg);
	delete reg;
}
