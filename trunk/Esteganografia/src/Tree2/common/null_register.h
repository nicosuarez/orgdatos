#ifndef __NULL_REGISTER_H_
#define __NULL_REGISTER_H_

#include "register.h"

/* Interfaz para registros */

class NullRegister : public Register{
	public:
		NullRegister(){}
		~NullRegister(){}

		Register* duplicate() const{ return new NullRegister(); }
		void setFields(const Register& b2){}
		unsigned int getSize()const{ return 0; }
		bool operator<(const Register& b2)const{ return true; }
		std::ostream& toOstream(std::ostream& out)const{ return out; }
		Register* getKeyRegister()const{ return new NullRegister(); }
};

#endif /* __NULL_REGISTER_H_ */
