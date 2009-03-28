#ifndef __BPP_ITERATOR_H__
#define __BPP_ITERATOR_H__

#include "treeIterator.h"
#include "leaf_register.h"
#include "leaf_node.h"
#include "node_manager.h"
#include <set>

class BppIterator : public TreeIterator {
	private:
		bool updated;
		unsigned int nodeOffset;
		NodeManager& manager;
		LeafNode* node;
		LeafNode::Registers::iterator it;
	public:
		BppIterator(unsigned int leafNodeOffset, NodeRegister& reg,NodeManager& nodeManager);
		~BppIterator();

		bool begin();
		bool end();

		TreeIterator& operator++();
		TreeIterator& operator--();

		key_val operator*();

		const Register& peekKey();
		const Register& peekValue();

		Register* getKey();
		Register* getValue();

		bool operator==(const TreeIterator& it);

		unsigned int getOffset()const{ return this->node->getOffset(); }
		NodeRegister* getPointer()const{ return *it; }

		void setOffset(unsigned int offset);
	private:
		void update();
};

#endif /* __BPP_ITERATOR_H__ */
