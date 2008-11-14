#include "bppIterator.h"

using namespace bpptree;

BppIterator::BppIterator(unsigned int leafNodeOffset, NodeRegister& reg, NodeManager* nodeManager){
	this->lNode = dynamic_cast<LeafNode*>(nodeManager->readNode(leafNodeOffset));
	LeafNode::Registers::iterator itStart = (lNode->regs).find(&reg);
	this->it = itStart; 
	this->nodeManag = nodeManager;
}
BppIterator::BppIterator(unsigned int leafNodeOffset, bool reverse, NodeManager* nodeManager){
	if(reverse){
		this->lNode = dynamic_cast<LeafNode*>(nodeManager->readNode(leafNodeOffset));
		LeafNode::Registers::iterator itStart = (lNode->regs).end();
		this->it = itStart; 
		this->nodeManag = nodeManager;}
	else{
		this->lNode = dynamic_cast<LeafNode*>(nodeManager->readNode(leafNodeOffset));
		LeafNode::Registers::iterator itStart = (lNode->regs).begin();
		this->it = itStart; 
		this->nodeManag = nodeManager;
	}
}

BppIterator::~BppIterator(){
	delete lNode;
}

bool BppIterator::EndOfFile(){
	bool ret;
	if((it==(lNode->regs).end())&&(lNode->getNextNode()==0))
		ret = true;
	else
		ret = false;
	return ret;
}

bool BppIterator::BeginOfFile(){
	bool ret;
	if((it==(lNode->regs).begin())&&(lNode->getPreviousNode()==0))
		ret = true;
	else
		ret = false;
	return ret;
}


TreeIterator* BppIterator::sig(){
	if(!EndOfFile()){
		it++;
		if((it==(lNode->regs).end())&&(lNode->getNextNode()!=0)){
			unsigned int aux = lNode->getNextNode();
			delete lNode;
			lNode = dynamic_cast<LeafNode*>(nodeManag->readNode(aux));
			it = lNode->sequenceBegin();
		}
	}
	return this;
}


TreeIterator* BppIterator::ant(){
	if(!BeginOfFile()){
		if((it==(lNode->regs).begin())&&(lNode->getPreviousNode()!=0)){
			unsigned int aux = lNode->getPreviousNode();
			delete lNode;
			lNode = dynamic_cast<LeafNode*>(nodeManag->readNode(aux));
			it = lNode->sequenceEnd();
		}
		it--;
	}
	return this;
}
	
Register* BppIterator::getRegister(){
	if(it!=lNode->sequenceEnd())
		return ((*it)->getRegister()).duplicate();
	else 
		return NULL;
}
