#include "level_node.h"
#include "node_manager.h"
#include "level_register.h"

LevelNode::LevelNode(unsigned int level,unsigned int leftChild,unsigned int offset,unsigned int size) : Node(level,offset,size){
	this->leftChild = leftChild;
}

LevelNode::~LevelNode(){
	for(Registers::iterator it = regs.begin(); it!=regs.end();++it){
		delete(*it);
	}
	regs.clear();
}

std::pair<Node*,NodeRegister*> LevelNode::split(){
	std::pair<Node*,NodeRegister*> splitResult;
	LevelNode* newNode = new LevelNode(this->level,NodeManager::NO_OFFSET,NodeManager::NO_OFFSET,this->size);
	newNode->insert( **this->regs.rbegin() );
	NodeRegister* toRemove = static_cast<NodeRegister*>((**this->regs.rbegin()).duplicate());
	this->remove( *toRemove );
	delete toRemove;

	/* Balancear la carga entre los 2 nodos*/
	/* Si hay un solo registro por nodo no hay nada que balancear */
	while( (this->getFreeSize()<newNode->getFreeSize() || this->usedSize>this->getNodeSize())  && this->registerCount>1){
		newNode->insert( **this->regs.rbegin() );
		toRemove = static_cast<NodeRegister*>((**this->regs.rbegin()).duplicate());
		this->remove( *toRemove );
		delete toRemove;
	}


	// Solo resta encontrar la clave que subira de nivel
	LevelRegister* regOverflow;
	regOverflow = static_cast<LevelRegister*>(newNode->extract(newNode->getFirst()));
	newNode->setLeftChild(regOverflow->getRightChild());

	splitResult.second = regOverflow;
	splitResult.first = newNode;

	this->offOverflow();
	return splitResult;
}

NodeRegister* LevelNode::getRootRegister(unsigned int offset){
	bool found=false;
	Node::Registers::iterator it=regs.begin();
	NodeRegister* ret=*it;
	if(offset!=this->leftChild){
		for(;it!=regs.end() && !found;++it){
			found = static_cast<LevelRegister*>(*it)->getRightChild()==offset;
			if(found)
				ret = *it;
		}
	}
	return ret;
}

unsigned int  LevelNode::getNextSibling(unsigned int offset){
	bool found=false;
	unsigned int ret = NodeManager::NO_OFFSET;
	Node::Registers::iterator it = this->regs.begin();

	if( found=(offset==this->getLeftChild())){
		ret = static_cast<LevelRegister*>(*it)->getRightChild();
	}

	for(;it!=regs.end() && !found;++it){
		if(static_cast<LevelRegister*>(*it)->getRightChild()==offset){
			++it;
			if( found=(it!=regs.end()) )
				ret = static_cast<LevelRegister*>(*it)->getRightChild();
			else
				--it; // No puedo pasarme del final
		}
	}
	return ret;
}

unsigned int  LevelNode::getPreviousSibling(unsigned int offset){
	bool found=false;
	unsigned int ret = NodeManager::NO_OFFSET;
	Node::Registers::iterator it = this->regs.begin();

	found=(offset==this->getLeftChild());

	for(;it!=regs.end() && !found;++it){
		if(static_cast<LevelRegister*>(*it)->getRightChild()==offset){

			if(found=(it==regs.begin()) )
				ret = this->getLeftChild();
			else{
				--it;
				ret = this->getLeftChild();
				ret = static_cast<LevelRegister*>(*it)->getRightChild();
				found = true;
			}
		}
	}
	return ret;
}

unsigned int LevelNode::getSubTree(const NodeRegister& reg){
	unsigned int retVal;
	LevelRegister temp(reg.getKey(),NodeManager::NO_OFFSET);

	std::pair<Registers::iterator,bool> p = regs.insert(&temp);
	/* Si se pudo insertar veo delante de que registro y obtengo el subarbol que apunte
	 * ese registro( o al que apunte el nodo si es el primero ) */
	if(p.second==true){
		if(p.first==regs.begin()){
			retVal = this->leftChild;
		}else{
			--p.first;
			retVal = dynamic_cast<LevelRegister*>((*(p.first)))->getRightChild();
			++p.first;
		}
		regs.erase(p.first);
	}else{
		/* La clave es justo un registro que esta en el nodo */
		retVal = dynamic_cast<LevelRegister*>((*(p.first)))->getRightChild();
	}

	return retVal;
}

unsigned int LevelNode::getHeaderSize()const{
	return (Node::getHeaderSize() + sizeof(leftChild));
}

char* LevelNode::toBytes(char* data,ControlRegisterFactory& factory)const{
	char* temp = Node::toBytes(data,factory);
	memcpy(temp,&this->leftChild,sizeof(leftChild));
	temp+=sizeof(leftChild);
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		temp = (*it)->toBytes(temp,factory);
	}
	return temp;
}

char* LevelNode::toNode(char* data,ControlRegisterFactory& factory){
	char* temp = Node::toNode(data,factory);
	memcpy(&this->leftChild,temp,sizeof(leftChild));
	temp+=sizeof(leftChild);

	unsigned int regCount = this->registerCount;
	for(unsigned int c=0;c<regCount;c++){
		LevelRegister* reg = new LevelRegister();
		temp = reg->toRegister(temp,factory);
		Node::insert(*reg);
		delete reg;
	}
	this->registerCount-=regCount;
	this->usedSize=this->calculateTotalSize(this->regs);

	return temp;
}


std::ostream& LevelNode::toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const{
	out << "/** Imprimiendo Nodo Nivel **/\n";
	out << "\t -- Informacion de cabecera ---\n";
	out << "\t Offset del Nodo : " << this->offset << "\n";

	if(this->leftChild!=NodeManager::NO_OFFSET)
		out << "\t Hijo Izquierdo : " << this->leftChild << "\n";
	else
		out << "\t Hijo Izquierdo : No existe" << "\n";

	out << "\t Cantidad de Registros : " << registerCount << "\n";
	out << "\t Espacio Libre : " << this->getFreeSize() << "\n";
	out << "\t Nivel : " << level << "\n";
	out << "\t -- Informacion de los registros ---\n";
	offsets.push(this->leftChild);
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		LevelRegister* reg = dynamic_cast<LevelRegister*>((*it));
		reg->toOstream(out);
		offsets.push(reg->getRightChild());
	}
	out << "/** Fin Nodo Nivel **/\n";
	return out;
}
