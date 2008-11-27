#include "Intruder.h"
#include "StrToken.h"
#include "Resource.h"
#include <iostream>


using std::cout;

Intruder::Intruder() {

}

Intruder::~Intruder() {
}

void Intruder::SetDate(Date date){
	this->date=date;
}
void Intruder::AddStr(string str){
	this->strings.push_back(str);
}

void Intruder::Deserialize(std::string str){
	tVecStr ans=StrToken::getStrTokens(str,"/");
	unsigned int year=atoi((ans[0]).c_str());
	unsigned int month=atoi((ans[1]).c_str());
	unsigned int day=atoi((ans[2]).c_str());
	unsigned int hour=atoi((ans[3]).c_str());
	unsigned int min=atoi((ans[4]).c_str());
	unsigned int seg=atoi((ans[5]).c_str());
	Date d(year,month,day,hour,min,seg);
	this->date=d;
	for(unsigned int i=6;i<ans.size();i++)
		this->strings.push_back(ans[i]);
}

void Intruder::toOstream()const{
	cout <<"Fecha: "<< this->date.getYear()+1900<<"/"<<this->date.getMonth()<<"/"<<this->date.getDay()<<"		"<<"Hora: "<<this->date.getHour()<<":"<<this->date.getMin()<<":"<<this->date.getSeg()<<"\n";
	cout<<MSG_INTRUDERS_GETPASS;
	for(unsigned int i=0;i<this->strings.size();i++)
		cout<<CIRCLE<<strings[i]<<"\n";

}
