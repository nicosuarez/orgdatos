#ifndef __BPPTREE__H__
#define __BPPTREE__H__

#include <iostream>
#include <string>
#include "node_manager.h"
#include "../Common/register.h"
#include "node.h"
#include "level_node.h"
#include "leaf_node.h"
#include "treeIterator.h"
#include "control_register_factory.h"

class BppTree{
	private:
		static const unsigned long OFFSET_ROOT = 0;
	private:
		NodeManager manager;
		Node* root;
		typedef std::set<TreeIterator*> Iterators;
		Iterators iterators;

	public:
		BppTree(unsigned int nodeSize,const RegisterFactory& keyFactory,const RegisterFactory& valFactory,const std::string& nodesFilename);
		~BppTree();

		bool empty();
		bool insert(const Register& key,const Register& value);
		bool remove(const Register& key);
		bool exists(const Register& key);
		Register* find(const Register& key);
		bool update(const Register& key,const Register& value);

		friend std::ostream& operator <<(std::ostream& out,BppTree& tree);

		TreeIterator& iterator(const Register& key);
		TreeIterator& last();
		TreeIterator& first();

		/* TODO -> dado que es opcional borrar los iteradores. debe crearse
		 * algun metodo para poder devolver uno existente cuando se llama a iterator
		 */
		void deleteIterator(TreeIterator& it);
	private:
		TreeIterator* getFirstNodeIterator(Node* root);
		TreeIterator* getLastNodeIterator(Node* root);
		TreeIterator* getNodeIterator(Node* root,NodeRegister& key);
		void updateIterators(unsigned int srcOffset,Node* modified,Node* neighbor);

		Register* nodeFind(Node* root,NodeRegister& key);

		bool nodeInsert(unsigned int nodeOffset,LevelNode* root,const NodeRegister& key,bool update=false);
		void handleLeafOverflow(LeafNode* leafNode,LevelNode* root);
		void handleLevelOverflow(LevelNode* levelNode,LevelNode* root);

		bool nodeRemove(unsigned int nodeOffset,LevelNode* root,const Register& key);
		void handleLeafUnderflow(LeafNode* leafNode,LevelNode* root);
		void joinLeafSibling(LeafNode* leafNode,LeafNode* nextNode,LevelNode* root,bool reverse);
		void getFromLeafSibling(LeafNode* leafNode,LeafNode* nextNode,LevelNode* root,bool reverse);

		void handleLevelUnderflow(LevelNode* levelNode,LevelNode* root);
		void joinLevelSibling(LevelNode* levelNode,LevelNode* nextNode,LevelNode* root,bool reverse);
		void getFromLevelSibling(LevelNode* levelNode,LevelNode* nextNode,LevelNode* root,bool reverse);
};


#endif /* __BPPTREE__H__ */
