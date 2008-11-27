#ifndef __BPP_NODE_H__
#define __BPP_NODE_H__

#include <set>
#include <cstring>
#include <queue>
#include <list>
#include "node_register.h"
#include "control_register_factory.h"

class Node{
	public:
		static const unsigned int LEAF_LEVEL = 0;
		static const unsigned int NO_LEVEL = -1;

		typedef std::set<NodeRegister*,NodeRegisterOrder> Registers;
	protected:
		unsigned int size;
		unsigned int level;
		unsigned int usedSize;
		unsigned int registerCount;
		unsigned int offset;
		bool foverflow;
		bool funderflow;
		bool fmodified;
		bool ffreed;

		Registers regs;
		Registers erasedRegs;

	public:
		Node(unsigned int level,unsigned int offset,unsigned int size);
		virtual ~Node();

		bool modified(){ return this->fmodified; }
		bool overflow(){ return this->foverflow; }
		bool underflow(){ return this->funderflow; }
		bool freed(){ return this->ffreed; }

		void offOverflow(){ this->foverflow = false; }
		void offModified(){ this->fmodified = false; }
		void offUnderflow(){ this->funderflow = false; }

		bool isLeaf(){ return level==LEAF_LEVEL; }

		virtual bool insert(const NodeRegister& reg);
		virtual	bool remove(const NodeRegister& reg);
		virtual	void extractAll(std::list<NodeRegister*>& regs);
		virtual	NodeRegister* extract(const NodeRegister& reg);
		virtual	std::pair<bool,Registers::iterator> search(NodeRegister& reg);
		Registers::iterator nearest(NodeRegister& reg);

		void setOffset(unsigned int offset){ this->offset = offset; }
		void setSize(unsigned int size){ this->size = size; }
		void setLevel(unsigned int level){ this->level = level; }
		void setUsedSize(unsigned int usedSize){ this->usedSize = usedSize; }
		void setRegisterCount(unsigned int registerCount){ this->registerCount = registerCount; }
		void setFreed(bool state){ this->ffreed = state; }

		unsigned int getOffset()const { return offset; }
		unsigned int getLevel()const { return level; }
		unsigned int getUsedSize()const { return usedSize; }
		unsigned int getRegisterCount()const { return registerCount; }
		unsigned int getNodeSize()const { return (size); }
		unsigned int getFreeSize()const;
		virtual unsigned int getHeaderSize()const;

		virtual std::pair<Node*,NodeRegister*> split()=0;

		virtual char* toNode(char* data,ControlRegisterFactory& factory);

		virtual char* toBytes(char* data,ControlRegisterFactory& factory)const;

		static unsigned int peekLevel(char* data){
			return ( *(unsigned int*)( data+sizeof(unsigned int) ) );
		}

		/* Inventada solo para poder aplicar polimorfismo con operator << que es friend */
		virtual std::ostream& toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const = 0;

		NodeRegister& getFirst(bool reverse=false);
		NodeRegister& getLast(bool reverse=false);
		bool isFirst(NodeRegister* reg);

		Registers::iterator begin(){ return regs.begin(); }
		Registers::iterator end(){ return regs.end(); }

		Registers::reverse_iterator rbegin(){ return regs.rbegin(); }
		Registers::reverse_iterator rend(){ return regs.rend(); }

		Registers::iterator ebegin(){ return erasedRegs.begin(); }
		Registers::iterator eend(){ return erasedRegs.end(); }

		void clearErased();

		unsigned int getUnderflowThreshold(){
			return (this->getNodeSize()-this->getHeaderSize())/4;
		}

		virtual unsigned int getHeaderSize(){
			return sizeof(level)+sizeof(registerCount);
		}

		bool joinable(const Node& n2,const NodeRegister& reg)const{
			unsigned int finalSize = this->getUsedSize()+reg.getSize()+n2.getUsedSize();
			unsigned int nodeEffectiveSize = this->getNodeSize()-this->getHeaderSize();
			return (finalSize<=nodeEffectiveSize);
		}

	protected:
		unsigned int calculateTotalSize(const Registers& regs)const;
		void setFlags();
};

#endif /* __BPP_NODE_H__ */
