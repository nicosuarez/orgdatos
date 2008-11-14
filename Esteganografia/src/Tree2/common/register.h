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
		virtual bool operator<(const Register& b2)const = 0;
		virtual std::ostream& toOstream(std::ostream& out)const = 0;

		/* !!AVISO -> si este registro va en un B+ DEBE extender este metodo */
		virtual Register* getKeyRegister()const { 
			throw ("Register -> DEBE EXTENDER EL METODO GET KEY REGISTER");
			return NULL; 
		}
};

class RegisterOrder{
	public:
		bool operator ()(Register* b1,Register* b2){
			return ((*b1)<(*b2));
		}
};

#endif /* __REGISTER_H_ */
