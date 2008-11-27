#ifndef __BPP_LEVEL_NODE_H__
#define __BPP_LEVEL_NODE_H__

#include "node.h"
#include "level_register.h"
#include <set>

class LevelNode : public Node{
	public:
		static const unsigned int NO_CHILD = -1;
	private:
		unsigned int leftChild;

	public:
		LevelNode(unsigned int level,unsigned int leftChild,unsigned int offset,unsigned int size);
		~LevelNode();

		unsigned int getHeaderSize() const;

		void setLeftChild(unsigned int offset){ this->leftChild = offset; }
		unsigned int getLeftChild(){ return this->leftChild;}

		unsigned int getSubTree(const NodeRegister& reg);
		NodeRegister* getRootRegister(unsigned int offset);
		unsigned int  getNextSibling(unsigned int offset);
		unsigned int  getPreviousSibling(unsigned int offset);

		std::pair<Node*,NodeRegister*> split();

		char* toBytes(char* data,ControlRegisterFactory& factory)const;
		char* toNode(char* data,ControlRegisterFactory& factory);

		std::ostream& toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const;

		virtual unsigned int getHeaderSize(){
			return (Node::getHeaderSize()+sizeof(leftChild));
		}
};

#endif /* __BPP_LEVEL_NODE_H__ */
