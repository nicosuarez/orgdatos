#ifndef __BPP_ITERATOR_H__
#define __BPP_ITERATOR_H__

#include "leaf_register.h"
#include "leaf_node.h"
#include "node_manager.h"
#include "register_pack.h"
#include <set>
#include "tree_pack.h"

namespace bpptree{

class BppIterator : public TreeIterator{
	private:
		LeafNode* lNode;
		LeafNode::Registers::iterator it;
		NodeManager* nodeManag;
	public:
		BppIterator(unsigned int leafNodeOffset, NodeRegister& reg, NodeManager* nodeManager);
		BppIterator(unsigned int leafNodeOffset, bool reverse, NodeManager* nodeManager);
		~BppIterator();

		bool EndOfFile();
		bool BeginOfFile();

		TreeIterator* sig();
		TreeIterator* ant();
		
		Register* getRegister();
}; 

}

#endif /* __BPP_ITERATOR_H__ */

