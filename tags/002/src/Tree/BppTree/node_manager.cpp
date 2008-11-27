#include <cstring>
#include <cstdio>
#include "node_manager.h"
#include "leaf_node.h"
#include "level_node.h"
#include "leaf_register.h"
#include "level_register.h"

NodeManager::NodeManager(const std::string& nodesFilename, unsigned int nodeSize,const RegisterFactory& keyFactory,const RegisterFactory& valFactory)
	: nodes(nodesFilename.c_str(),std::fstream::in | std::fstream::out | std::fstream::binary) {
	
	if(!nodes){
		nodes.open(nodesFilename.c_str(),std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
		nodes.clear();
	}

	freeOffsetsFilename = nodesFilename+std::string("-tmp");
	std::string offsetRegPath = nodesFilename+std::string("-big-regs");

	readFreeNodeBlocks();
	this->nodeSize = nodeSize;

	factory = new ControlRegisterFactory(keyFactory,valFactory,offsetRegPath);
}

NodeManager::~NodeManager(){
	writeFreeNodeBlocks();
	delete this->factory;
}

void NodeManager::writeNode(Node& node){
	unsigned int nodeOffset = node.getOffset();
	if(nodeOffset==NO_OFFSET) nodeOffset = getFreeNodeBlock();
	nodes.clear();
	nodes.seekp(nodeOffset);
	char* bytes = new char[nodeSize];
	/* Para que el valgrind no moleste */
	memset(bytes,0,sizeof(char)*nodeSize);

	if(node.getLevel()==Node::LEAF_LEVEL)
		node.toBytes(bytes,*factory);
	else
		node.toBytes(bytes,*factory);

	nodes.write(bytes,nodeSize);
	node.setOffset(nodeOffset);
	node.offModified();
	node.setFreed(false);
	delete[] bytes;
}

Node* NodeManager::readNode(unsigned int nodeOffset){
	Node* node = NULL;
	char* bytes = new char[nodeSize];
	memset(bytes,0,sizeof(char)*nodeSize);
	nodes.clear();	
	nodes.seekg(nodeOffset);
	nodes.peek();
	if(!nodes.eof()){
		nodes.read(bytes,nodeSize);

		if(Node::peekLevel(bytes)==Node::LEAF_LEVEL){
			node = new LeafNode(Node::LEAF_LEVEL,nodeOffset,nodeSize);
			node->toNode(bytes,*factory);
		}else{
			node = new LevelNode(Node::NO_LEVEL,LevelNode::NO_CHILD,nodeOffset,nodeSize);
			node->toNode(bytes,*factory);
		}
		node->offModified();
	}else{
		// Nodo hoja vacio ( Para que se inicialize la raiz )
		node = new LeafNode(Node::LEAF_LEVEL,nodeOffset,nodeSize);
	}

	delete[] bytes;
	return node;
}

unsigned int NodeManager::fillNewNodeSize(){
	unsigned int nodeOffset = getFreeNodeBlock();;
	nodes.clear();	
	nodes.seekp(nodeOffset);
	char* bytes = new char[nodeSize];
	memset(bytes,0,sizeof(char)*nodeSize);
	nodes.write(bytes,nodeSize);
	delete[] bytes;
	return nodeOffset;
}

void NodeManager::freeNodeBlock(Node& node){
	node.setFreed(true);
	freeNodes.push(node.getOffset());
	node.setOffset(NO_OFFSET);
}

unsigned int NodeManager::getFreeNodeBlock(){
	if(freeNodes.empty()){
		nodes.seekg(0,std::fstream::end);
		return nodes.tellg();
	}else{
		int ret = freeNodes.front();
		freeNodes.pop();
		return ret;
	}
}

void NodeManager::readFreeNodeBlocks(){	
	std::ifstream in(freeOffsetsFilename.c_str());

	// No hay nada que hacer no exiten bloques libres.
	if(!in)
		return;

	while(!in.eof()){
		unsigned int temp;
		in.read( (char*)(&temp),sizeof(unsigned int) );
		in.peek();
		freeNodes.push(temp);
	}
}

void NodeManager::writeFreeNodeBlocks(){
	/* Sobrescribo el anterior total todos offsets libres estan en memoria ya */
	remove(freeOffsetsFilename.c_str());
	/* Si no existen offsets libres el archivo no tiene razon de existir */
	if(!freeNodes.empty()){
		std::ofstream out(freeOffsetsFilename.c_str());

		while(!freeNodes.empty()){
			unsigned int temp = freeNodes.front();
			out.write( (char*)(&temp),sizeof(unsigned int) );
			freeNodes.pop();
		}
	}
}
