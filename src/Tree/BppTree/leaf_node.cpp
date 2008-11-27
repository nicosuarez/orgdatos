#include "leaf_node.h"
#include "leaf_register.h"
#include "node_manager.h"
#include "level_register.h"

LeafNode::LeafNode(unsigned int level,unsigned int offset,unsigned int size) : Node(level,offset,size){
	this->previousNode = NodeManager::NO_OFFSET;
	this->nextNode = NodeManager::NO_OFFSET;
}

LeafNode::~LeafNode(){
	for(Registers::iterator it = regs.begin(); it!=regs.end();++it){
		delete(*it);
	}
	regs.clear();
}

std::pair<Node*,NodeRegister*> LeafNode::split(){
	std::pair<Node*,NodeRegister*> splitResult;
	LeafNode* newNode = new LeafNode(this->level,NodeManager::NO_OFFSET,this->size);
	newNode->insert( this->getFirst(true) );
	delete this->extract( this->getFirst(true) );

	/* Balancear la carga entre los 2 nodos*/
	/* Si hay un solo registro por nodo no hay nada que balancear */
	while(this->getFreeSize()<newNode->getFreeSize() && this->registerCount>1){
		newNode->insert( this->getFirst(true) );
		delete this->extract( this->getFirst(true) );
	}

	/* Solo resta encontrar la clave que subira de nivel,
	 * esa clave es la ultima que paso hacia la derecha*/
	splitResult.second = new LevelRegister(newNode->getFirst().getKey(),NodeManager::NO_OFFSET);
	splitResult.first = newNode;

	this->offOverflow();
	return splitResult;
}

unsigned int LeafNode::getHeaderSize()const{
	return Node::getHeaderSize()+sizeof(previousNode)+sizeof(nextNode);
}

char* LeafNode::toBytes(char* data,ControlRegisterFactory& factory)const {
	char* temp = Node::toBytes(data,factory);
	memcpy(temp,&previousNode,sizeof(previousNode));
	temp += sizeof(previousNode);
	memcpy(temp,&nextNode,sizeof(nextNode));
	temp += sizeof(nextNode);
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		temp = (*(it))->toBytes(temp,factory);
	}

	return temp;
}

char* LeafNode::toNode(char* data,ControlRegisterFactory& factory){
	char* temp = Node::toNode(data,factory);
	memcpy((void*)&previousNode,temp,sizeof(previousNode));
	temp+=sizeof(previousNode);
	memcpy((void*)&nextNode,temp,sizeof(nextNode));
	temp+=sizeof(nextNode);

	unsigned int regCount = this->registerCount;
	for(unsigned int c=0;c<regCount;c++){
		LeafRegister* reg = new LeafRegister();
		temp = reg->toRegister(temp,factory);
		Node::insert(*reg);
		delete reg;
	}
	this->registerCount-=regCount;
	this->usedSize=this->calculateTotalSize(this->regs);

	return temp;
}

std::ostream& LeafNode::toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const{
	out << "/** Imprimiendo Nodo Hoja **/\n";
	out << "\t -- Informacion de cabecera ---\n";
	out << "\t Offset del Nodo : " << this->offset << "\n";
	out << "\t Cantidad de Registros : " << registerCount << "\n";
	out << "\t Espacio Libre : " << getFreeSize() << "\n";
	out << "\t Nivel : " << level << "\n";

	if(nextNode==NodeManager::NO_OFFSET)
		out << "\t Siguiente : No existe"<< "\n";
	else
		out << "\t Siguiente : "<<nextNode<< "\n";

	if(previousNode==NodeManager::NO_OFFSET)
		out << "\t Anterior : No existe"<<"\n";
	else
		out << "\t Anterior : "<<previousNode<<"\n";

	out << "\t -- Informacion de los registros ---\n";
	for(Registers::iterator it=regs.begin();it!=regs.end();++it){
		(*it)->toOstream(out);
	}
	out << "/** Fin Nodo Hoja **/\n";
	return out;
}

