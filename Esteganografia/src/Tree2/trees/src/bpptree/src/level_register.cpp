#include "level_register.h"
#include <cstring>

using namespace bpptree;

LevelRegister::LevelRegister(){
}

LevelRegister::LevelRegister(const Register& reg ,unsigned int rightChild){	
	this->rightChild= rightChild;
	this->reg = reg.duplicate();
}

LevelRegister::LevelRegister(const LevelRegister& lr){	
	this->rightChild =lr.getRightChild();
	this->reg = lr.getRegister().duplicate();
	
}

LevelRegister::~LevelRegister(){
	delete this->reg;
}

NodeRegister* LevelRegister::duplicate()const{
	return (new LevelRegister(*this));
}

unsigned int LevelRegister::getSize() const{
	/* Tamaño de registro mas puntero */

	return(sizeof(unsigned int) + (this->getRegister()).getSize());

}

char* LevelRegister::toBytes(char* data,const RegisterFactory& factory)const{
	char* temp = data;
	temp = factory(*reg,temp);	
	memcpy(temp,&(this->rightChild),sizeof(unsigned int));
	temp+=sizeof(unsigned int);
	return temp;
}

char* LevelRegister::toRegister(char* data,const RegisterFactory& factory){
	char* temp = data;
	this->reg = factory(temp);
	temp += this->reg->getSize();
	memcpy(&this->rightChild,temp,sizeof(unsigned int));
	temp+=sizeof(unsigned int);
	return temp;
}

std::ostream& LevelRegister::toOstream(std::ostream& out)const{
	out << "\t\t Clave: ";
	reg->toOstream(out);
	out<< std::endl;
	out << "\t\t Hijo Derecho: " << this->rightChild << std::endl;
	return out;
}


