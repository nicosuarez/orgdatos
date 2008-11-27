#ifndef __BPP_LEAF_NODE_H__
#define __BPP_LEAF_NODE_H__

#include <set>
#include "node.h"

class LeafNode : public Node{
	private:
		unsigned int nextNode;
		unsigned int previousNode;
	public:
		LeafNode(unsigned int level,unsigned int offset,unsigned int size);
		~LeafNode();

		char* toBytes(char* data,ControlRegisterFactory& factory)const;
		char* toNode(char* data,ControlRegisterFactory& factory);

		std::ostream& toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const;

		unsigned int getHeaderSize()const;

		void setNextNode(unsigned int nextN){this->nextNode = nextN;}
		unsigned int getNextNode(){return nextNode;}

		void setPreviousNode(unsigned int previousN){this->previousNode = previousN;};
		unsigned int getPreviousNode(){return previousNode;}

		std::pair<Node*,NodeRegister*> split();

		virtual unsigned int getHeaderSize(){
			return (Node::getHeaderSize()+sizeof(nextNode)+sizeof(previousNode));
		}
};

#endif /* __BPP_LEAF_NODE_H__ */
