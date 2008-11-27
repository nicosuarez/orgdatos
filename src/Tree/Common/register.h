#ifndef __REGISTER_H_
#define __REGISTER_H_

#include <iostream>

/* Interfaz para registros */

class Register{
	public:
		Register(){}
		virtual ~Register(){}

		virtual Register* duplicate() const = 0;
		virtual void setFields(const Register& b2) = 0;
		virtual unsigned int getSize()const = 0;
		virtual bool operator<(const Register& r2)const=0;
		virtual std::ostream& toOstream(std::ostream& out)const = 0;
};

/* Comparador de registros */

class RegisterOrder{
	public:
		virtual ~RegisterOrder();
		virtual bool operator ()(Register& b1,Register& b2) = 0;
};

#endif /* __REGISTER_H_ */
