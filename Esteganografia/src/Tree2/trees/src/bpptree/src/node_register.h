#ifndef __BPP_NODE_REGISTER_H__
#define __BPP_NODE_REGISTER_H__

#include "register_pack.h"

namespace bpptree{

class NodeRegister{
	protected:
		Register* reg;
	public:
		NodeRegister(){}
		virtual ~NodeRegister(){}

		virtual NodeRegister* duplicate()const = 0;

		virtual unsigned int getSize()const = 0;

		virtual std::ostream& toOstream(std::ostream& out)const = 0;

		virtual char* toBytes(char* data,const RegisterFactory& factory)const = 0;
			
		virtual char* toRegister(char* data,const RegisterFactory& factory) = 0;

		bool operator <(const NodeRegister& l2) const{
			Register* reg = l2.getRegister().duplicate();
			bool ret = ((*(this->reg))<(*reg));
			delete reg;
			return ret;
			
		}

		Register& getRegister()const{ return *(this->reg); }
};


class NodeRegisterOrder{
	public:
		bool operator()(const NodeRegister* l1,const NodeRegister* l2) const{
			return((*l1)<(*l2));
		}
};

}

#endif /* __BPP_NODE_REGISTER_H__ */
