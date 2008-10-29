#include "node.h"

Node::Node(unsigned int level,unsigned int offset,unsigned int size){
	this->usedSize=0;
	this->registerCount=0;
	this->level = level;
	this->size = size;
	this->offset = offset;
	this->funderflow = false;
	this->foverflow = false;
	this->fmodified = false;
	this->ffreed = false;
}

Node::~Node(){
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		delete(*it);
	}
	regs.clear();
	clearErased();
}

void Node::clearErased(){
	for(Registers::iterator it=erasedRegs.begin();it!=erasedRegs.end();++it){
		delete(*it);
	}
	erasedRegs.clear();
}

bool Node::insert(const NodeRegister& reg){
	NodeRegister* temp = static_cast<NodeRegister*>(reg.duplicate());
	std::pair<Registers::iterator,bool> p = regs.insert(temp);
	if(p.second){
		usedSize+=temp->getSize();
		registerCount++;

		setFlags();
	}
	else
		delete temp;

	return p.second;
}

bool Node::remove(const NodeRegister& reg){
	bool ret=false;
	std::pair<Registers::iterator,bool> erasedP;
	Registers::iterator it = regs.find((NodeRegister*)&reg);
	if(it!=regs.end()){
		registerCount--;
		usedSize-=(*it)->getSize();
		ret = true;

		erasedP = erasedRegs.insert(*it);
		if(!erasedP.second)
			delete *it;

		regs.erase(it);

		setFlags();
	}

	return ret;
}

void Node::setFlags(){
	if( !this->getFreeSize() ) {
		this->foverflow 	= true;
		this->funderflow	= false;
	}else if( this->getUsedSize()<this->getUnderflowThreshold() ) {
		this->funderflow 	= true;
		this->foverflow 	= false;
	}else{
		this->funderflow 	= false;
		this->foverflow 	= false;
	}

	this->fmodified = true;
}

bool Node::isFirst(NodeRegister* reg){
	return (regs.find(reg)==regs.begin());
}

NodeRegister& Node::getFirst(bool reverse){
	if(!reverse)
		return (**this->regs.begin());
	return (**this->regs.rbegin());
}

NodeRegister& Node::getLast(bool reverse){
	if(!reverse)
		return (**this->regs.rbegin());
	return (**this->regs.begin());
}

void Node::extractAll(std::list<NodeRegister*>& regs){
	for(Node::Registers::iterator it=this->regs.begin();it!=this->regs.end();++it){
		regs.push_back(*it);
	}
	this->regs.clear();
	this->usedSize=0;
	this->registerCount=0;
	setFlags();
}

NodeRegister* Node::extract(const NodeRegister& reg){
	NodeRegister* ret = NULL;
	Node::Registers::iterator it = regs.find((NodeRegister*)&reg);
	if(it!=regs.end()){
		ret = *it;
		registerCount--;
		usedSize-=(*it)->getSize();
		setFlags();
		regs.erase(it);
	}
	return ret;
}

Node::Registers::iterator Node::nearest(NodeRegister& reg){
	Node::Registers::iterator pointer = regs.begin();
	bool found=false;

	while(!found){
		found = (pointer==regs.end());
		if(!found){
			if(!(**pointer<reg)){
				if(pointer!=regs.begin())
					--pointer;
				found = true;
			}

			if(!found)
				++pointer;
		}
	}
	if(pointer==regs.end())
		--pointer;

	return pointer;
}

std::pair<bool,Node::Registers::iterator> Node::search(NodeRegister& reg){
	std::pair<bool,Registers::iterator> ret(false,regs.end());
	ret.second = regs.find(&reg);
	ret.first  = (ret.second!=regs.end());
	return ret;
}

unsigned int Node::getFreeSize()const{
	if(size>usedSize+getHeaderSize())
		return (size-usedSize-getHeaderSize());
	return 0;
}

unsigned int Node::getHeaderSize()const{
	return sizeof(registerCount)+sizeof(level);
}

unsigned int Node::calculateTotalSize(const Registers& regs)const{
	unsigned int acum=0;
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		acum+=(*it)->getSize();
	}
	return acum;
}

char* Node::toNode(char* data,ControlRegisterFactory& factory){
	char* temp = data;
	memcpy((void*)&registerCount,temp,sizeof(registerCount));
	temp+=sizeof(registerCount);
	memcpy((void*)&level,temp,sizeof(level));
	temp+=sizeof(level);
	return temp;
}

char* Node::toBytes(char* data,ControlRegisterFactory& factory)const {
	char* temp = data;
	memcpy(temp,&registerCount,sizeof(registerCount));
	temp += sizeof(registerCount);
	memcpy(temp,&level,sizeof(level));
	temp += sizeof(level);
	return temp;
}
