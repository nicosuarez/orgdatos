#ifndef __BPP_LEVEL_REGISTER_H
#define __BPP_LEVEL_REGISTER_H

#include "register_pack.h"
#include "node_register.h"

namespace bpptree{

class LevelRegister : public NodeRegister {
	private:
		unsigned int  rightChild;
	public:
		LevelRegister();
		LevelRegister(const Register& reg ,unsigned int rightChild);
		LevelRegister(const LevelRegister& lr);
		~LevelRegister();

		void setRightChild(unsigned int offset){ this->rightChild = offset; }
		unsigned int getRightChild()const{ return rightChild; }
		
		unsigned int getSize()const;		
		NodeRegister* duplicate()const;
		char* toBytes(char* data,const RegisterFactory& factory)const;			
		char* toRegister(char* data,const RegisterFactory& factory);
		std::ostream& toOstream(std::ostream& out)const;
		//bool operator<(const NodeRegister& l2) const;
	
};

class LevelRegisterOrder{
	public:
		bool operator()(const LevelRegister* l1,const LevelRegister* l2) const{
			return((*l1)<(*l2));
		}
};

}

#endif /* __BPP_LEVEL_REGISTER_H */
