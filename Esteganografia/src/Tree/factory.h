#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <iostream>
#include <cstring>

#include "Common/register.h"
#include "Common/register_factory.h"

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
			this->value = ((Value&)b2).value;
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

class KeySt : public Register{
	protected:
		std::string key;

	public:
		KeySt(const std::string& key){
			this->key = key;
		}

		virtual ~KeySt(){
		}

		virtual Register* duplicate() const{ return new KeySt(*this); }

		std::string getKey()const{ return this->key; }

		void setFields(const Register& b2){
			this->key = ((KeySt&)b2).key;
		}

		unsigned int getSize()const{
			return (key.length()+1);
		}

		bool operator <(const Register& r2)const{
			return key< ((const KeySt&)r2).key;
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			Key* k = (Key*)this;
			out << "\tKey = " << k->key.substr(0,5) << "\n";
			//out << "\tKey = " << this->key << "\n";
			return out;
		}
};

class ValueNull : public Register{
	public:
		ValueNull(){
		}

		~ValueNull(){
		}

		virtual Register* duplicate() const{ return new ValueNull(*this); }

		void* getKey()const{ return NULL }

		void setFields(const Register& b2){
			this->key = ((ValueNull&)b2).key;
		}

		unsigned int getSize()const{
			return (key.length()+1);
		}

		bool operator <(const Register& r2)const{
			return key< ((const KeySt&)r2).key;
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			Key* k = (Key*)this;
			out << "\tKey = " << k->key.substr(0,5) << "\n";
			//out << "\tKey = " << this->key << "\n";
			return out;
		}
};

class DummyKeyFactory : public RegisterFactory{
	public:
		DummyKeyFactory(){}
		virtual ~DummyKeyFactory(){}

		virtual RegisterFactory* duplicate()const{ return new DummyKeyFactory(); }

		char* operator()(Register& reg,char* data){
			Key& akey = dynamic_cast<Key&>(reg);

			std::string keystr  = akey.getKey();

			strcpy(data,keystr.c_str());
			data+=akey.getSize();

			return data;
		}

		virtual Register* operator()(char* data){
			return new Key(std::string(data));
		}
};

class DummyValueNullFactory : public DummyKeyFactory{
	public:
		DummyValueNullFactory(){}
		~DummyValueNullFactory(){}

		RegisterFactory* duplicate()const{ return new DummyValueNullFactory(); }

		virtual Register* operator()(char* data){
			return new ValueNull(std::string(data));
		}
};

class DummyValFactory : public RegisterFactory{
	public:
		DummyValFactory(){}
		~DummyValFactory(){}

		RegisterFactory* duplicate()const{ return new DummyValFactory(); }

		char* operator()(Register& reg,char* data){
			Value& avalue = dynamic_cast<Value&>(reg);

			unsigned int valint  = avalue.getValue();

			memcpy(data,(char*)&valint,avalue.getSize());
			data+=avalue.getSize();

			return data;
		}

		Register* operator()(char* data){
			return new Value(*((unsigned int*)data));
		}
};

#endif /* __FACTORY_H__ */
