#ifndef __BPP_LEAF_NODE_H__
#define __BPP_LEAF_NODE_H__

#include <set>
#include "node.h"
#include "register_pack.h"
#include "node_register.h"

namespace bpptree{

class LeafNode : public Node{
	private:
		unsigned int nextNode;
		unsigned int previousNode;
	public:
		LeafNode(unsigned int level,unsigned int offset,unsigned int size);
		~LeafNode();

		bool insert(const NodeRegister& reg);
		bool remove(NodeRegister& reg);
		

		char* toBytes(char* data,const RegisterFactory& factory)const;
		char* toNode(char* data,const RegisterFactory& factory);

		std::ostream& toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const;

		void setNextNode(unsigned int nextN){this->nextNode = nextN;}
		unsigned int getNextNode(){return nextNode;}

		void setPreviousNode(unsigned int previousN){this->previousNode = previousN;};
		unsigned int getPreviousNode(){return previousNode;}

		NodeRegister* joinNodes(Node* nodo);

		NodeRegister* extractLastRegister();
		NodeRegister* extractFirstRegister();

		bool modify(NodeRegister& nodeRegister);

		friend class BppIterator;
};

}

#endif /* __BPP_LEAF_NODE_H__ */
