#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <iostream>
#include <cstring>
#include <string>
#include <utility>
#include <glibmm/ustring.h>
#include "Common/register.h"
#include "Common/register_factory.h"

using Glib::ustring;

class ValueInt : public Register{
	private:
		unsigned int value;

	public:
		ValueInt(unsigned int value){
			this->value = value;
		}

		~ValueInt(){
		}

		virtual Register* duplicate() const{ return new ValueInt(*this); }

		unsigned int getValue()const{ return this->value; }

		void setFields(const Register& b2){
			this->value = ((ValueInt&)b2).value;
		}

		unsigned int getSize()const{
			return (sizeof(value));
		}

		bool operator <(const Register& r2)const{
			return true;// No se comparan values
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			out << "\tValue = " << this->value << "\n";
			return out;
		}
};

class KeyStr : public Register{
	protected:
		ustring key;

	public:
		KeyStr(ustring key){
			this->key = key;
		}

		//KeyStr(const KeyStr& key){
		//	this->key = key.key;
		//}

		virtual ~KeyStr(){
		}

		virtual Register* duplicate() const{ return new KeyStr(*this); }

		ustring getKey()const{ return this->key; }

		void setFields(const Register& b2){
			this->key = ((KeyStr&)b2).key;
		}

		unsigned int getSize()const{
			return (key.length()+1);
		}

		bool operator <(const Register& r2)const{
			return key< ((const KeyStr&)r2).key;
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			KeyStr* k = (KeyStr*)this;
			out << "\tKeySt = " << k->key.c_str()<< "\n";
			return out;
		}
};

class ValueIntFactory : public RegisterFactory{
	public:
		ValueIntFactory(){}
		~ValueIntFactory(){}

		RegisterFactory* duplicate()const{ return new ValueIntFactory(); }

		char* operator()(Register& reg,char* data){
			ValueInt& avalue = dynamic_cast<ValueInt&>(reg);

			unsigned int valint  = avalue.getValue();

			memcpy(data,(char*)&valint,avalue.getSize());
			data+=avalue.getSize();

			return data;
		}

		Register* operator()(char* data){
			return new ValueInt(*((unsigned int*)data));
		}
};

class KeyStrFactory : public RegisterFactory{
	public:
		KeyStrFactory(){}
		virtual ~KeyStrFactory(){}

		virtual RegisterFactory* duplicate()const{ return new KeyStrFactory(); }

		char* operator()(Register& reg,char* data){
			KeyStr& akey = dynamic_cast<KeyStr&>(reg);

			ustring keystr  = akey.getKey();

			strcpy(data,keystr.c_str());
			data+=akey.getSize();

			return data;
		}

		virtual Register* operator()(char* data){
			return new KeyStr(ustring(data));
		}
};


#endif /* __FACTORY_H__ */
