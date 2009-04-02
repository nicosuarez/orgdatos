#include "bppIterator.h"
#include "leaf_node.h"
#include "level_node.h"
#include "../Exception/iterator_out_of_range.h"
#include "control_register.h"

BppIterator::BppIterator(unsigned int leafNodeOffset, NodeRegister& reg, NodeManager& nodeManager)
: manager(nodeManager){
	this->nodeOffset = leafNodeOffset;
	this->updated = false;
	this->node = dynamic_cast<LeafNode*>(manager.readNode(leafNodeOffset));
	this->it = node->search(reg).second;
	if(this->it==node->end())
		this->it= node->nearest(reg); // Busco el inmediatamente inferior
}

BppIterator::~BppIterator(){
	delete node;
}

bool BppIterator::end(){
	if(this->updated)
		update();

	bool ret;
	if((it==node->end())&&(node->getNextNode()==NodeManager::NO_OFFSET))
		ret = true;
	else
		ret = false;
	return ret;
}

bool BppIterator::begin(){
	if(this->updated)
		update();

	bool ret;
	if((it==node->end())&&(node->getPreviousNode()==NodeManager::NO_OFFSET))
		ret = true;
	else
		ret = false;
	return ret;
}


TreeIterator& BppIterator::operator++(){
	if(this->updated)
		update();

	if(it!=node->end())
		++it;

	if(it==node->end() && node->getNextNode()!=NodeManager::NO_OFFSET){
		unsigned int aux = node->getNextNode();
		delete node;
		node = dynamic_cast<LeafNode*>(manager.readNode(aux));
		it = node->begin();
	}

	return *this;
}


TreeIterator& BppIterator::operator--(){
	if(this->updated)
		update();

	if(!begin()){
		if(node->getPreviousNode()!=NodeManager::NO_OFFSET){
			unsigned int aux = node->getPreviousNode();
			delete node;
			node = dynamic_cast<LeafNode*>(manager.readNode(aux));
			it = node->begin();
		}
		it--;
	}
	return *this;
}

key_val BppIterator::operator*(){
	if(this->updated)
		update();

	std::pair<Register*,Register*> ret(NULL,NULL);
	if(it!=node->end()){
		ret.first = dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>(*it)->getKey()).getRegister().duplicate();
		ret.second = dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>(*it)->getValue()).getRegister().duplicate();
	}

	return ret;
}

const Register& BppIterator::peekKey(){
	if(this->updated)
			update();

	if(it==node->end()) throw IteratorOutOfRange("BppIterator out of range");
	return dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>(*it)->getKey()).getRegister();
}

const Register& BppIterator::peekValue(){
	if(this->updated)
		update();

	if(it==node->end()) throw IteratorOutOfRange("BppIterator out of range");
	return dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>(*it)->getValue()).getRegister();
}

Register* BppIterator::getKey(){
	if(this->updated)
		update();

	if(it==node->end()) throw IteratorOutOfRange("BppIterator out of range");
	return dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>(*it)->getKey()).getRegister().duplicate();
}

Register* BppIterator::getValue(){
	if(this->updated)
		update();

	if(it==node->end()) throw IteratorOutOfRange("BppIterator out of range");
	return dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>(*it)->getValue()).getRegister().duplicate();
}

bool BppIterator::operator==(const TreeIterator& it){
	if(this->updated)
		update();

	const BppIterator& crit = dynamic_cast<const BppIterator&>(it);

	if(this->nodeOffset!=crit.getOffset())
		return false;

	return ((*this->it)->getKey()<(*(crit.it))->getKey() && (*(crit.it))->getKey()<(*this->it)->getKey());
}

void BppIterator::setOffset(unsigned int offset){
	this->nodeOffset = offset;
	this->updated = true;
}

void BppIterator::update(){
	this->updated = false;

	/* Guardo temporalmente el registro apuntado */
	NodeRegister* pointer = static_cast<NodeRegister*>((*it)->duplicate());
	delete this->node;

	node = dynamic_cast<LeafNode*>(manager.readNode(this->nodeOffset));
	std::pair<bool,LeafNode::Registers::iterator> p = node->search(*pointer);
	delete pointer;

	if(!p.first){
		/* El registro apuntado fue borrado se situa al principio del nodo */
		p = node->search(node->getFirst());
	}

	this->it = p.second;
}
