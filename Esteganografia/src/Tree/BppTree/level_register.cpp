#include "level_register.h"
#include <cstring>

LevelRegister::LevelRegister(){
}

LevelRegister::LevelRegister(const Register& key ,unsigned int rightChild) : NodeRegister(key) {
	this->rightChild= rightChild;
}

LevelRegister::LevelRegister(const LevelRegister& lr) : NodeRegister(*lr.key) {
	this->rightChild = lr.getRightChild();
}

LevelRegister::~LevelRegister(){
}

NodeRegister* LevelRegister::duplicate()const{
	return (new LevelRegister(*this));
}

unsigned int LevelRegister::getSize() const{
	/* Tamaño de registro mas puntero */
	return(NodeRegister::getSize()+sizeof(this->rightChild) + this->key->getSize() );
}

char* LevelRegister::toBytes(char* data,ControlRegisterFactory& factory)const{
	char* temp = NodeRegister::toBytes(data,factory);
	memcpy(temp,&(this->rightChild),sizeof(unsigned int));
	temp+=sizeof(this->rightChild);
	return temp;
}

char* LevelRegister::toRegister(char* data,ControlRegisterFactory& factory){
	char* temp = NodeRegister::toRegister(data,factory);
	memcpy(&this->rightChild,temp,sizeof(this->rightChild));
	temp+=sizeof(this->rightChild);
	return temp;
}

std::ostream& LevelRegister::toOstream(std::ostream& out)const{
	out << "\t\t Clave: ";
	key->toOstream(out);
	out<< std::endl;
	out << "\t\t Hijo Derecho: " << this->rightChild << std::endl;
	return out;
}


