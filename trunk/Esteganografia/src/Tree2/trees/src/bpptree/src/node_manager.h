#ifndef __BPP_NODE_MANAGER_H__
#define __BPP_NODE_MANAGER_H__

#include <string>
#include <fstream>
#include <queue>
#include "register_pack.h"
#include "node.h"

namespace bpptree{

class NodeManager{
	public:
		static const unsigned int NO_OFFSET = -1;
	private:
		/* Archivo temporal utilizado para darle persistencia
           a los offsets libres en el archivo de nodos*/ 
		std::string freeOffsetsFilename;
		std::fstream nodes;
		std::queue<unsigned int> freeNodes;
		unsigned int nodeSize;
		RegisterFactory* factory;
		RegisterFactory* factoryNivel;

	public:
		NodeManager(const std::string& nodesFilename,unsigned int nodeSize,const RegisterFactory& factory,const RegisterFactory& factoryNiv);
		~NodeManager();

		void writeNode(Node& node);
		Node* readNode(unsigned int offset);
		void freeNodeBlock(Node& node);

		unsigned int getNodeSize(){ return nodeSize; }

	private:
		unsigned int getFreeNodeBlock();
		void writeFreeNodeBlocks();
		void readFreeNodeBlocks();
};

}

#endif /* __BPP_NODE_MANAGER_H__ */
