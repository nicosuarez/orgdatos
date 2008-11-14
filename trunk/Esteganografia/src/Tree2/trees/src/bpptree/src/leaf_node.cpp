#include "leaf_node.h"
#include "node_manager.h"
#include "leaf_register.h"
#include "level_register.h"

using namespace bpptree;

LeafNode::LeafNode(unsigned int level,unsigned int offset,unsigned int size) : Node(level,offset,size){
}

LeafNode::~LeafNode(){
	for(Registers::iterator it = regs.begin(); it!=regs.end();++it){
		delete(*it);
	}
	regs.clear();
}

bool LeafNode::insert(const NodeRegister& reg){
	if(!Node::insert(reg))return false;	
	if( (regs.size()*reg.getSize()) >(this->getSize()-16)){
		/* overflow */
		/* localizar el elemento del medio si el tamaño es fijo 
           sino este algoritmo es otro */
		Registers::iterator it = regs.begin();
		for(unsigned int c=0;c<regs.size()/2;c++,++it);
		Register* lR = dynamic_cast<LeafRegister*>(*it)->getKeyRegister();
		overflowRegister = new LevelRegister(*lR,NodeManager::NO_OFFSET);
		delete lR;
		//overflowRegister = dynamic_cast<LeafRegister*>(*it)->getKeyRegister();
		/* crear el nuevo nodo */		
		newNode = new LeafNode(this->level,NodeManager::NO_OFFSET,this->size);


		Registers::iterator it2 = it;		
		for(;it!=regs.end();++it){
			newNode->insert(*(*it));
			delete(*it);
		}



		regs.erase(it2,regs.end());
		this->foverflow = true;
		registerCount = regs.size();

	}else{
		this->fmodified = true;
	}

	return true;
}

bool LeafNode::remove(NodeRegister& reg){
	bool ret = Node::remove(reg);
	if(getRegCount()<2/*Cantidad de regMax Hoja TODO*/)
		this->funderflow = true;
	else 
		this->fmodified = true;	
	return ret;
}

char* LeafNode::toBytes(char* data,const RegisterFactory& factory)const {
	char* temp = Node::toBytes(data,factory);
	memcpy(temp,&previousNode,sizeof(unsigned int));
	temp += sizeof(unsigned int);
	memcpy(temp,&nextNode,sizeof(unsigned int));
	temp += sizeof(unsigned int);
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		temp = (*(it))->toBytes(temp,factory);
	}	
	return temp;
}
		
char* LeafNode::toNode(char* data,const RegisterFactory& factory){
	char* temp = Node::toNode(data,factory);
	memcpy((void*)&previousNode,temp,sizeof(unsigned int));
	temp+=sizeof(unsigned int);
	memcpy((void*)&nextNode,temp,sizeof(unsigned int));
	temp+=sizeof(unsigned int);
	for(unsigned int c=0;c<registerCount;c++){
		LeafRegister* reg = new LeafRegister();
		temp = reg->toRegister(temp,factory);
		regs.insert(reg);
	}
	return temp;
}

std::ostream& LeafNode::toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const{
	out << "/** Imprimiendo Nodo Hoja **/" << std::endl;
	out << "\t -- Informacion de cabecera ---" << std::endl;
	out << "\t Offset del Nodo : " << this->offset << std::endl;
	out << "\t Cantidad de Registros : " << registerCount << std::endl;
	out << "\t Nivel : " << level << std::endl;
	out << "\t Siguiente : "<<nextNode<<std::endl;
	out << "\t Anterior : "<<previousNode<<std::endl;
	out << "\t -- Informacion de los registros ---" << std::endl;
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){		
		(*it)->toOstream(out);
	}	
	out << "/** Fin Nodo Hoja **/" << std::endl;
	return out;
}

NodeRegister* LeafNode::joinNodes(Node* nodo){
	NodeRegister* nodoIntermedio = Node::joinNodes(nodo);
	LeafNode* leaf = dynamic_cast<LeafNode*>(nodo);
/*	if(leaf->getFirstRegister()<this->getFirstRegister()){
		this->setPreviousNode(leaf->getPreviousNode());
		nodoIntermedio = this->getFirstRegister();
	}
	else{*/
	this->setNextNode(leaf->getNextNode());
	/*}*/
	Register* kr = (dynamic_cast<LeafRegister*>(nodoIntermedio))->getKeyRegister();
	NodeRegister* re = new LevelRegister(*kr, NodeManager::NO_OFFSET);
	delete kr;
	delete nodoIntermedio;
	return re;
}

NodeRegister* LeafNode::extractFirstRegister(){ 
	NodeRegister* NR = Node::extractFirstRegister();
	if(getRegCount()<2/*Cantidad de regMax Nivel TODO*/)
		this->funderflow = true;
	else 
		this->fmodified = true;	
	return NR;
}

NodeRegister* LeafNode::extractLastRegister(){ 
	NodeRegister* NR = Node::extractLastRegister();
	if(getRegCount()<2/*Cantidad de regMax Nivel TODO*/)
		this->funderflow = true;
	else 
		this->fmodified = true;	
	return NR;
}

bool LeafNode::modify(NodeRegister& nodeRegister){
	bool ret = false;
	LeafRegister* leafRegister = dynamic_cast<LeafRegister*>(&nodeRegister);
	Registers::iterator it = regs.find(leafRegister);
	if(it!=regs.end()){
		((*it)->getRegister()).setFields(leafRegister->getRegister());
		ret = true;
	}
	return ret;
}

