#ifndef __BPPTREE__H__
#define __BPPTREE__H__

#include <iostream>
#include <string>
#include "node_manager.h"
#include "register_pack.h"
#include "node.h"
#include "leaf_node.h"
#include "level_node.h"
#include "bppIterator.h"
#include "tree_pack.h"

namespace bpptree{

class BppTree : public Tree{
	private:
		static const unsigned long OFFSET_ROOT = 0;
	private:
		NodeManager manager;
		Node* root;
		/* para acelerar las cosas la raiz siempre esta en memoria 
			TODO -> recordar todo el camino de busqueda*/

	public:
		BppTree(unsigned int nodeSize,const RegisterFactory& factory,const RegisterFactory& factoryNivel,const std::string& nodesFilename);
		~BppTree();

		bool insert(const Register& reg);
		bool remove(const Register& reg);
		bool search(Register& reg);
		bool modify(const Register& reg);
		
		BppIterator* getIterator(const Register& reg);
		
		BppIterator* getFirst();
		BppIterator* getLast();
		
		friend std::ostream& operator <<(std::ostream& out,BppTree& tree)
		{

			Node* node = tree.manager.readNode(BppTree::OFFSET_ROOT);
			std::queue<unsigned int> offsets;
			out << "*------Comienzo Arbol B+----------*" << std::endl;
			node->toOstream(out,offsets);
			while(!offsets.empty()){		
				unsigned int off = offsets.front();
				offsets.pop();
				Node* temp = tree.manager.readNode(off);
				temp->toOstream(out,offsets); /* suma al queue offsets */
				delete temp;
			}
			out << "*------Fin Arbol B+----------*" << std::endl;
			delete node;
			return out;
		}
		
	private:
		bool nodeInsert(unsigned int nodeOffset,LevelNode* root,const Register& reg);
		void handleLevelOverflow(LevelNode* levelnode,LevelNode* root);
		void handleLeafOverflow(LeafNode* leafNode,LevelNode* root);
		bool nodeRemove(unsigned int nodeOffset,LevelNode* root,const Register& reg);
		void handleLeafUnderflow(LeafNode* leafNode,LevelNode* root,const Register& reg);
		void handleLevelUnderflow(LevelNode* levelNode,LevelNode* root,const Register& reg);
		
		/* Por si se usa polimorfismo desde Tree */
		std::ostream& toOstream(std::ostream& out);
};

}

#endif /* __BPPTREE__H__ */
