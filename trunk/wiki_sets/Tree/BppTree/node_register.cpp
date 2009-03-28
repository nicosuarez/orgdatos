#include "node_register.h"

NodeRegister::NodeRegister(const Register& key){
	this->key = key.duplicate();
}

NodeRegister::~NodeRegister(){
	delete this->key;
}


void NodeRegister::setFields(const Register& r2){
	this->getKey().setFields(dynamic_cast<const NodeRegister&>(r2).getKey());
}

unsigned int NodeRegister::getSize()const{
	return sizeof(key->getSize());
}

char* NodeRegister::toBytes(char* data,ControlRegisterFactory& factory)const{
	char* temp = data;
	temp = factory(*key,temp);
	return temp;
}

char* NodeRegister::toRegister(char* data,ControlRegisterFactory& factory){
	char* temp = data;
	this->key = factory(temp);
	temp += this->key->getSize();
	return temp;
}
