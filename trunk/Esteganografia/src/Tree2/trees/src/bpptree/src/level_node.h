#ifndef __BPP_LEVEL_NODE_H__
#define __BPP_LEVEL_NODE_H__

#include "node.h"
#include "register_pack.h"
#include "level_register.h"
#include <set>

namespace bpptree{

class LevelNode : public Node{
	public:
	static const unsigned int NO_CHILD = -1;
	private:
		unsigned int leftChild;

	public:
		LevelNode(unsigned int level,unsigned int leftChild,unsigned int offset,unsigned int size);
		~LevelNode();

		unsigned int getSize() const;

		void setLeftChild(unsigned int offset){ this->leftChild = offset; }
		unsigned int getLeftChild(){ return this->leftChild;}
		bool isFirst(const NodeRegister& reg)const;

		bool insert(const NodeRegister& reg);
		bool remove(NodeRegister& reg);
		NodeRegister* modify(NodeRegister& regAnterior,NodeRegister& regNuevo);

		std::pair<bool,unsigned int> getSubTree(const Register& reg);

		char* toBytes(char* data,const RegisterFactory& factory)const;
		char* toNode(char* data,const RegisterFactory& factory);

		//first>0 si trae proximo sibling; first<0 si trae sibling anterior
		std::pair<int, std::pair<LevelRegister*,unsigned int> > getSibling(LevelRegister* reg);
		NodeRegister* joinNodes(Node* nodo, LevelRegister* rootRegister);

		NodeRegister* extractLastRegister();
		NodeRegister* extractFirstRegister();

		std::ostream& toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const;
		std::ostream& toOstream2(std::ostream& out)const;
};

}

#endif /* __BPP_LEVEL_NODE_H__ */
