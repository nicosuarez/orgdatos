#ifndef __REGISTER_FACTORY_H__
#define __REGISTER_FACTORY_H__

#include "register.h"

class RegisterFactory{
	public:
		RegisterFactory(){}
		virtual ~RegisterFactory(){}

		virtual	Register* operator ()(char* data)const =0 ;
		virtual char* operator ()(const Register& reg,char* data)const =0;

		virtual RegisterFactory* duplicate()const = 0;
};

#endif /* __REGISTER_FACTORY_H__ */
