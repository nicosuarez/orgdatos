#include "level_node.h"
#include "node_manager.h"
#include "level_register.h"

using namespace bpptree;

LevelNode::LevelNode(unsigned int level,unsigned int leftChild,unsigned int offset,unsigned int size) : Node(level,offset,size){
	this->leftChild = leftChild;
}

LevelNode::~LevelNode(){
	for(Registers::iterator it = regs.begin(); it!=regs.end();++it){
		delete(*it);
	}
	regs.clear();
}

bool LevelNode::insert(const NodeRegister& reg){
	if(!Node::insert(reg)) return false;

	if(regs.size()*reg.getSize()>(this->getSize()-8)){
		/* overflow */

		/* localizar el elemento del medio */
		Registers::iterator it = regs.begin();
		for(unsigned int c=0;c<(unsigned int)regs.size()/2;c++,++it);
		overflowRegister = (*it);

		/* crear el nuevo nodo */
		newNode = new LevelNode(this->level, dynamic_cast<LevelRegister*>((*it))->getRightChild(), NodeManager::NO_OFFSET, this->size);
		Registers::iterator it2 = it;
		it++;
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

bool LevelNode::remove(NodeRegister& reg){
	Registers::iterator it = regs.lower_bound(&reg);
	
	if(it!=regs.end()){
		if((reg<*(*it))&&(it!=regs.begin()))
			it--;
	}
	else{
		it--;
	}
	bool ret = Node::remove(*(*it));
	if(getRegCount()<2)//Cantidad de regMax Nivel TODO
		this->funderflow = true;
	else 
		this->fmodified = true;	
	return ret;
}

bool LevelNode::isFirst(const NodeRegister& reg) const{
	/* si a==b => !(a<b) y !(a>b) */
	NodeRegister* first = *regs.begin();
	return (!( (*first)<(reg) )&&!( reg<*(first) ));
}

std::pair<bool,unsigned int> LevelNode::getSubTree(const Register& reg){
	std::pair<bool,unsigned int> retVal;
	const NodeRegister* temp2;
	Registers::iterator iter = regs.begin(); 
	retVal.second = this->leftChild;
	temp2 = dynamic_cast<NodeRegister*>((*iter));	
	while((iter!=regs.end())&&((temp2->getRegister())<reg)){
		retVal.second = (dynamic_cast<LevelRegister*>((*iter)))->getRightChild();
		iter++;
		temp2 = dynamic_cast<NodeRegister*>((*iter));
	}
	if(iter!=regs.end()){
		if(!(reg<(temp2->getRegister())))
			retVal.second = (dynamic_cast<LevelRegister*>((*iter)))->getRightChild();
	}

	retVal.first = true;	
	return retVal;
}

unsigned int LevelNode::getSize()const{
	/* Debe restarse el puntero al menor hijo izquierdo dado que no forma parte
       de ningun registro del nodo */
	return ( Node::getSize() - sizeof(unsigned int) ); 
}

char* LevelNode::toBytes(char* data,const RegisterFactory& factory)const{
	char* temp = Node::toBytes(data,factory);
	memcpy(temp,&this->leftChild,sizeof(unsigned int));
	temp+=sizeof(unsigned int);
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		temp = (*it)->toBytes(temp,factory);
	}
	return temp;
}
		
char* LevelNode::toNode(char* data,const RegisterFactory& factory){
	char* temp = Node::toNode(data,factory);
	memcpy(&this->leftChild,temp,sizeof(unsigned int));
	temp+=sizeof(unsigned int);
	for(unsigned int c=0;c<registerCount;c++){
		LevelRegister* reg = new LevelRegister();
		temp = reg->toRegister(temp,factory);
		regs.insert(reg);
	}
	return temp;
}


std::ostream& LevelNode::toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const{
	out << "/** Imprimiendo Nodo Nivel **/" << std::endl;
	out << "\t -- Informacion de cabecera ---" << std::endl;
	out << "\t Offset del Nodo : " << this->offset << std::endl;
	out << "\t Hijo Izquierdo : " << this->leftChild << std::endl;
	out << "\t Cantidad de Registros : " << registerCount << std::endl;
	out << "\t Nivel : " << level << std::endl;
	out << "\t -- Informacion de los registros ---" << std::endl;
	offsets.push(this->leftChild);
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){		
		LevelRegister* reg = dynamic_cast<LevelRegister*>((*it));
		reg->toOstream(out);
		offsets.push(reg->getRightChild());
	}	
	out << "/** Fin Nodo Nivel **///" << std::endl;
	return out;
}

std::ostream& LevelNode::toOstream2(std::ostream& out)const{
	out << "/** Imprimiendo Nodo Nivel **/" << std::endl;
	out << "\t -- Informacion de cabecera ---" << std::endl;
	out << "\t Offset del Nodo : " << this->offset << std::endl;
	out << "\t Hijo Izquierdo : " << this->leftChild << std::endl;
	out << "\t Cantidad de Registros : " << registerCount << std::endl;
	out << "\t Nivel : " << level << std::endl;
	out << "\t -- Informacion de los registros ---" << std::endl;
	
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){		
		LevelRegister* reg = dynamic_cast<LevelRegister*>((*it));
		//LevelRegister* reg = (LevelRegister*)((*it));
		reg->toOstream(out);
	}	
	out << "/** Fin Nodo Nivel **///" << std::endl;
	return out;
}

std::pair<int, std::pair<LevelRegister*,unsigned int> > LevelNode::getSibling(LevelRegister* reg){
	//std::pair<int, unsigned int> ret;
	std::pair<int, std::pair<LevelRegister*,unsigned int> > ret;
	Registers::iterator it = regs.lower_bound(reg);
	if(it!=regs.end()){
		/*Si es igual todabia le falta uno para el siguiente*/
		if(!(*reg<(*dynamic_cast<LevelRegister*>(*it))))
			it++;
		if(it!=regs.end()){
			ret.first = 1;
			ret.second.first = dynamic_cast<LevelRegister*>((*it)->duplicate());
			ret.second.second = (dynamic_cast<LevelRegister*>(*it))->getRightChild();
		}
		else{	//Busco anterior
			it--;
			ret.second.first = dynamic_cast<LevelRegister*>((*it)->duplicate());
			if(regs.begin()!=it){
				it--;
				ret.second.second = (dynamic_cast<LevelRegister*>(*it))->getRightChild();
				ret.first = -1;
			}else{
				ret.first = -1;
				ret.second.second = leftChild;
			}
		}
	}
	else{
		//Busco anterior porque es mayor que el ultimo
		ret.first = -1;
		it--;
		ret.second.first = dynamic_cast<LevelRegister*>((*it)->duplicate());
		if(regs.begin()!=it){
			it--;
			ret.first = -1;
			ret.second.second = (dynamic_cast<LevelRegister*>(*it))->getRightChild();
		}else{
			ret.first = -1;
			ret.second.second = leftChild;	
		}	
	}
	return ret;
}



NodeRegister* LevelNode::modify(NodeRegister& regAnterior,NodeRegister& regNuevo){
	//modifca el contenido de un registro y lo carga en la lista modifcado
	NodeRegister* retorno;
	Registers::iterator it = regs.lower_bound(&regAnterior);
	
	if(it!=regs.end()){
		if((regAnterior<*(*it))&&(it!=regs.begin()))
			it--;
	}
	else{
		it--;
	}
	retorno = (*it)->duplicate();
	(dynamic_cast<LevelRegister*>(&regNuevo))->setRightChild((dynamic_cast<LevelRegister*>(*it))->getRightChild());	
	delete (*it);
	regs.erase(it);
	std::pair<Registers::iterator,bool> p = regs.insert(regNuevo.duplicate());
	this->fmodified = true;	
	return retorno;
	
}

NodeRegister* LevelNode::joinNodes(Node* nodo, LevelRegister* rootRegister){
	/*Agrega a este nodo los registros del otro nodo*/
	/*Copio el root Register y le cambio clave*/
	rootRegister->setRightChild((dynamic_cast<LevelNode*>(nodo))->getLeftChild());
	std::pair<Registers::iterator,bool> p = regs.insert(rootRegister->duplicate());
	registerCount++;
	/*Copio registros del otro nodo*/
	NodeRegister* primeroDelEliminado = Node::joinNodes(nodo);
	
	return primeroDelEliminado;
}

NodeRegister* LevelNode::extractFirstRegister(){ 
	NodeRegister* NR = Node::extractFirstRegister();
	if(getRegCount()<2/*Cantidad de regMax Nivel TODO*/)
		this->funderflow = true;
	else 
		this->fmodified = true;	
	return NR;
}

NodeRegister* LevelNode::extractLastRegister(){ 
	NodeRegister* NR = Node::extractLastRegister();
	if(getRegCount()<2/*Cantidad de regMax Nivel TODO*/)
		this->funderflow = true;
	else 
		this->fmodified = true;	
	return NR;
}





