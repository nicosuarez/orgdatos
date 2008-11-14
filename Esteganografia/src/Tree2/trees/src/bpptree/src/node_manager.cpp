#include "node_manager.h"
#include "leaf_node.h"
#include "level_node.h"
#include <cstring>
#include <cstdio>

using namespace bpptree;

NodeManager::NodeManager(const std::string& nodesFilename, unsigned int nodeSize,const RegisterFactory& factory,const RegisterFactory& factoryNiv) : nodes(nodesFilename.c_str(),std::ios::binary |	std::ios::in | std::ios::out ) {
	freeOffsetsFilename = nodesFilename+std::string(".tmp");
	if(!nodes){
		/* El archivo se crea por primera vez */
		nodes.open(nodesFilename.c_str(),std::fstream::binary |	std::fstream::in | std::fstream::out | std::fstream::trunc );
	}else{
		readFreeNodeBlocks();
	}
	this->nodeSize = nodeSize;
	this->factory = factory.duplicate();
	this->factoryNivel = factoryNiv.duplicate();
}

NodeManager::~NodeManager(){
	writeFreeNodeBlocks();
	delete this->factory;
	delete this->factoryNivel;
}

void NodeManager::writeNode(Node& node){
	unsigned int nodeOffset = node.getOffset();
	if(nodeOffset==NO_OFFSET) nodeOffset = getFreeNodeBlock();
	nodes.clear();
	nodes.seekp( nodeOffset,std::fstream::beg	 );	
	char* bytes = new char[nodeSize];
	/* Para que el valgrind no moleste */
	memset(bytes,0,sizeof(char)*nodeSize);

	if(node.getLevel()==Node::LEAF_LEVEL)
		node.toBytes(bytes,*factory);
	else
		node.toBytes(bytes,*factoryNivel);

	nodes.write(bytes,nodeSize);
	node.setOffset(nodeOffset);
	delete[] bytes;
}

Node* NodeManager::readNode(unsigned int nodeOffset){
	Node* node;
	char* bytes = new char[nodeSize];
	memset(bytes,0,sizeof(char)*nodeSize);
	nodes.clear();
	nodes.seekg( nodeOffset,std::fstream::beg );	
	nodes.read(bytes,nodeSize);
	if(Node::peekLevel(bytes)==Node::LEAF_LEVEL){
		node = new LeafNode(Node::NO_LEVEL,nodeOffset,nodeSize);
		node->toNode(bytes,*factory);
	}else{
		node = new LevelNode(Node::NO_LEVEL,LevelNode::NO_CHILD,nodeOffset,nodeSize);
		node->toNode(bytes,*factoryNivel);
	}
		
	delete[] bytes;
	return node;
}

void NodeManager::freeNodeBlock(Node& node){
	freeNodes.push(node.getOffset());
	node.setOffset(NO_OFFSET);
}

unsigned int NodeManager::getFreeNodeBlock(){
	if(freeNodes.empty()){
		nodes.seekg( 0,std::fstream::end );
		return nodes.tellg();
	}else{
		int ret = freeNodes.front();
		freeNodes.pop();
		return ret;
	}
}

void NodeManager::readFreeNodeBlocks(){
	std::ifstream in(freeOffsetsFilename.c_str(),std::fstream::binary);
	if(!in)
		return; /* El archivo no existe por lo tanto no hay nodos libres */	
				
	while(!in.eof()){
		unsigned int temp;
		in.read( (char*)(&temp),sizeof(unsigned int) );
		freeNodes.push(temp);
		in.peek(); /* Activa el EOF */
	}
}

void NodeManager::writeFreeNodeBlocks(){
	/* Sobrescribo el anterior total todos offsets libres estan en memoria ya */
	std::ofstream out(freeOffsetsFilename.c_str(),std::fstream::binary );
	
	/* Si no existen offsets libres el archivo no tiene razon de existir */
	if(freeNodes.empty()){
		out.close();
		remove(freeOffsetsFilename.c_str());
	}
	else{
		while(!freeNodes.empty()){
			unsigned int temp = freeNodes.front();
			out.write( (char*)(&temp),sizeof(unsigned int) );
			freeNodes.pop();
		}
	}
}
