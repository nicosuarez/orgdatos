#ifndef __BPP_LEAF_REGISTER_H__
#define __BPP_LEAF_REGISTER_H__

#include "node_register.h"
#include "register_pack.h"

namespace bpptree{

/* Esta clase existe solo por el bien del diseño ya que
   no es mas que un alias de la clase NodeRegister */
class LeafRegister : public NodeRegister{
	public:
		LeafRegister(){}
		LeafRegister(const Register& reg) {
			this->reg = reg.duplicate();
		}

		LeafRegister(const LeafRegister& LeafReg){
			this->reg = LeafReg.getRegister().duplicate();
		}

		~LeafRegister(){
			delete this->reg;
		}

		Register& getRegister()const{ return *(this->reg); }

		NodeRegister* duplicate()const{
			return (new LeafRegister(*this));
		}

		unsigned int getSize()const{
			return reg->getSize();
		};

		std::ostream& toOstream(std::ostream& out)const{
			reg->toOstream(out);
			return out;
		}

		char* toBytes(char* data,const RegisterFactory& factory)const{
			char* temp = data;
			temp = factory(*reg,temp);
			return temp;
		}
			
		char* toRegister(char* data,const RegisterFactory& factory){
			char* temp = data;
			this->reg = factory(temp);
			temp += this->reg->getSize();
			return temp;
		}

		Register* getKeyRegister()const{
			return this->reg->getKeyRegister();
		}
};

}

#endif /* __BPP_LEAF_REGISTER_H__ */
