#ifndef __REGISTER_FILE_FACTORY_H__
#define __REGISTER_FILE_FACTORY_H__

#include "../Common/register.h"
#include "../Common/register_factory.h"
#include "control_register.h"

class RegisterFileFactory : public RegisterFactory{
	private:
		RegisterFactory* keyFactory;
		RegisterFactory* valFactory;

	public:
		RegisterFileFactory(const RegisterFactory& keyFactory,const RegisterFactory& valFactory){
			this->keyFactory = keyFactory.duplicate();
			this->valFactory = valFactory.duplicate();
		}

		RegisterFileFactory(const RegisterFileFactory& rff){
			this->keyFactory = rff.keyFactory->duplicate();
			this->valFactory = rff.valFactory->duplicate();
		}

		~RegisterFileFactory(){
			delete keyFactory;
			delete valFactory;
		}

		RegisterFactory* duplicate()const{ return new RegisterFileFactory(*this); }

		char* operator ()(Register& reg,char* data){
			ControlRegister& cr = dynamic_cast<ControlRegister&>(reg);
			data[0] = cr.getFlags();
			data += 1;
			if (cr.isKeyType()){
				data = (*keyFactory)(cr.getRegister(),data);
			}else{
				data = (*valFactory)(cr.getRegister(),data);
			}
			return data;
		}

		Register* operator ()(char* data){
			char flags = data[0];
			data += 1;
			Register* reg = NULL;
			ControlRegister* ret = new ControlRegister(flags);
			if(flags&ControlRegister::KEY_TYPE){
				reg = (*keyFactory)(data);
			}else{
				reg = (*valFactory)(data);
			}
			ret->setRegister(reg);
			return ret;
		}
};

#endif /* __REGISTER_FILE_FACTORY__ */
