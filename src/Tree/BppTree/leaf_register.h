#ifndef __BPP_LEAF_REGISTER_H__
#define __BPP_LEAF_REGISTER_H__

#include "node_register.h"

class LeafRegister : public NodeRegister{
	private:
		Register* value;
	public:
		LeafRegister(){}
		LeafRegister(const Register& key,const Register& value) : NodeRegister(key) {
			this->value = value.duplicate();
		}

		LeafRegister(const LeafRegister& leaf) : NodeRegister(*leaf.key) {
			this->value = leaf.getValue().duplicate();
		}

		virtual ~LeafRegister(){
			delete this->value;
		}

		virtual Register& getValue()const{ return *(this->value); }

		virtual Register* duplicate()const{
			return (new LeafRegister(*this));
		}

		virtual unsigned int getSize()const{
			return NodeRegister::getSize()+key->getSize()+value->getSize();
		};

		virtual void setFields(const Register& r2){
			NodeRegister::setFields(r2);
			const LeafRegister& lr = dynamic_cast<const LeafRegister&>(r2);
			this->getValue().setFields(lr.getValue());
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			this->getKey().toOstream(out);
			this->getValue().toOstream(out);
			return out;
		}

		virtual char* toBytes(char* data,ControlRegisterFactory& factory)const{
			char* temp = NodeRegister::toBytes(data,factory);
			temp = factory(*value,temp);
			return temp;
		}

		virtual char* toRegister(char* data,ControlRegisterFactory& factory){
			char* temp = NodeRegister::toRegister(data,factory);
			this->value = factory(temp);
			temp += this->value->getSize();
			return temp;
		}
};

#endif /* __BPP_LEAF_REGISTER_H__ */
