#ifndef __BPP_NODE_REGISTER_H__
#define __BPP_NODE_REGISTER_H__

#include "../Common/register.h"
#include "control_register_factory.h"

class NodeRegister : public Register{
	protected:
		Register* key;
	public:
		NodeRegister(){}
		NodeRegister(const Register& key);
		virtual ~NodeRegister();

		virtual Register* duplicate()const = 0;

		virtual unsigned int getSize()const;

		virtual void setFields(const Register& r2);

		virtual std::ostream& toOstream(std::ostream& out)const = 0;

		virtual char* toBytes(char* data,ControlRegisterFactory& factory)const;
		virtual char* toRegister(char* data,ControlRegisterFactory& factory);


		bool operator <(const Register& l2) const{
			return (this->getKey())<(dynamic_cast<const NodeRegister&>(l2).getKey());
		}

		Register& getKey()const{ return *(this->key); }
};


class NodeRegisterOrder{
	public:
		bool operator()(const NodeRegister* l1,const NodeRegister* l2) const{
			return((*l1)<(*l2));
		}
};

#endif /* __BPP_NODE_REGISTER_H__ */
