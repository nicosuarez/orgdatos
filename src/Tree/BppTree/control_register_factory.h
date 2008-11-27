#ifndef __CONTROL_REGISTER_FACTORY_H__
#define __CONTROL_REGISTER_FACTORY_H__

#include <list>
#include "../Common/register.h"
#include "../Common/register_factory.h"
#include "../RegisterFile/register_file.h"
#include "control_register.h"
#include "register_file_factory.h"

class ControlRegisterFactory{
	private:
		static const unsigned int CELL_SIZE = 1024;

		RegisterFileFactory factory;
		RegisterFile file;

	public:
		ControlRegisterFactory(const RegisterFactory& keyFactory,const RegisterFactory& valFactory,const std::string& offsetFile) :
			factory(keyFactory,valFactory),
			file(offsetFile,factory,CELL_SIZE){

		}

		virtual ~ControlRegisterFactory(){}

		virtual	Register* operator ()(char* data){
			ControlRegister* ret = NULL;
			if(data[0]&ControlRegister::OVER_THRESHOLD){
				/* Se trata de un offset solamente */
				unsigned int offset = *(unsigned int*)(data+1);
				ret = static_cast<ControlRegister*>(file.read(offset));
				ret->setOverOn();
				ret->setOffset(offset);
			}else{
				/* Es solamente el registro */
				ret = static_cast<ControlRegister*>(factory(data));
			}
			return ret;
		}

		virtual char* operator ()(Register& reg,char* data){
			ControlRegister& ct = dynamic_cast<ControlRegister&>(reg);
			if(ct.isOver()){
				unsigned int offset=ControlRegister::NO_OFFSET;
				/* Guardo el registro en el register file y paso a bytes el offset */
				ct.setOverOff();
				if(ct.getOffset()==ControlRegister::NO_OFFSET)
					offset = file.write(ct);
				else
					offset = file.write(ct,ct.getOffset());
				ct.setOverOn();
				ct.setOffset(offset);

				data[0] = ct.getFlags();
				data += 1;
				memcpy(data,&offset,sizeof(offset));
				data += sizeof(offset);
			}else{
				/* Solamanete guardo el registro */
				data = factory(ct,data);
			}
			return data;
		}
};

#endif /* __CONTROL_REGISTER_FACTORY_H__ */
