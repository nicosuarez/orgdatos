#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <iostream>
#include <cstring>
#include <string>
#include <utility>

#include "../Common/Resource.h"
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

class ValueNull : public Register{
	public:
		ValueNull(){}

		~ValueNull(){
		}

		virtual Register* duplicate() const{ return new ValueNull(*this); }

		void getValue()const{}

		void setFields(const Register& b2){}

		unsigned int getSize()const{
			return (0);
		}

		bool operator <(const Register& r2)const{
			return true;// No se comparan values
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			//out << "\tValue = " << this->value << "\n";
			return out;
		}
};

class KeyFreeSpace : public Register{
	protected:
		std::pair<ID_type,unsigned long> key;

	public:
		
		KeyFreeSpace(ID_type freeSpaceId, unsigned long size) : key(freeSpaceId, size){
		}
		
		KeyFreeSpace(std::pair<ID_type,unsigned long> key ) : key(key){
			
		}

		virtual ~KeyFreeSpace(){
		}
		
		virtual Register* duplicate() const{ return new KeyFreeSpace(*this); }

		std::pair<ID_type,unsigned long> GetKey()const
		{
			return this->key; 
		}
		
		void setFields(const Register& b2){
			this->key = ((KeyFreeSpace&)b2).key;
		}

		unsigned int getSize()const{
			return (sizeof(std::pair <ID_type,unsigned long>));
		}

		bool operator <(const Register& r2)const
		{
			bool compare = false;
			if(key.second > ((const KeyFreeSpace&)r2).key.second)
			{
				compare = true;
			}
			else
			{
				if(key.second == ((const KeyFreeSpace&)r2).key.second)
				{
					compare = (key.first > ((const KeyFreeSpace&)r2).key.first);
				}
			}
			return compare;
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			KeyFreeSpace* k = (KeyFreeSpace*)this;
			out << "\tFreeSpaceID = " << k->key.first<< "\n";
			out << "\tSize = " << k->key.second<< "\n";
			return out;
		}
};

class KeyFreeSpaceFactory : public RegisterFactory{
	public:
		KeyFreeSpaceFactory(){}
		virtual ~KeyFreeSpaceFactory(){}

		virtual RegisterFactory* duplicate()const{ return new KeyFreeSpaceFactory(); }

		char* operator()(Register& reg,char* data){
			KeyFreeSpace& akey = dynamic_cast<KeyFreeSpace&>(reg);
			std::pair<ID_type,unsigned long> key =akey.GetKey();
			
			memcpy(data,(char*)&key, akey.getSize());
			data+=akey.getSize();

			return data;
		}

		virtual Register* operator()(char* data){
			return new KeyFreeSpace(*((std::pair<ID_type,unsigned long>*)data));
		}
};

class ValueFreeSpace : public Register{

	protected:
		std::pair<ID_type,unsigned long> value;

	public:
		
		Register* duplicate() const{ return new ValueFreeSpace(*this); }
		
		ValueFreeSpace(ID_type imgId, unsigned long position) : value(imgId,position){
		}
		
		ValueFreeSpace(std::pair<ID_type,unsigned long> value ) : value(value){
			
		}
		
		virtual ~ValueFreeSpace(){
		}

		std::pair<ID_type,unsigned long> GetValue()const
		{
			return this->value; 
		}
			
		void setFields(const Register& b2){
			this->value = ((ValueFreeSpace&)b2).value;
		}

		unsigned int getSize()const{
			return (sizeof(std::pair <ID_type,unsigned long>));
		}

		bool operator <(const Register& r2)const
		{
			return true; //No se comparan values.
		}
	
		std::ostream& toOstream(std::ostream& out)const{
			ValueFreeSpace* k = (ValueFreeSpace*)this;
			out << "\tImgID = " << k->value.first<< "\n";
			out << "\tPosition = " << k->value.second<< "\n";
			return out;
		}
};

class ValueFreeSpaceFactory : public KeyFreeSpaceFactory{
	
public:
		ValueFreeSpaceFactory(){}
		~ValueFreeSpaceFactory(){}

		RegisterFactory* duplicate()const{ return new ValueFreeSpaceFactory(); }
		
		char* operator()(Register& reg,char* data){
			ValueFreeSpace& aVal = dynamic_cast<ValueFreeSpace&>(reg);
			std::pair<ID_type,unsigned long> val =aVal.GetValue();
			
			memcpy(data,(char*)&val, aVal.getSize());
			data+=aVal.getSize();

			return data;
		}
		
		virtual Register* operator()(char* data){
			return new ValueFreeSpace(*((std::pair<ID_type,unsigned long>*)data));
		}

};


class KeyStr : public Register{
	protected:
		std::string key;

	public:
		KeyStr(std::string key){
			this->key = key;
		}

		//KeyStr(const KeyStr& key){
		//	this->key = key.key;
		//}

		virtual ~KeyStr(){
		}

		virtual Register* duplicate() const{ return new KeyStr(*this); }

		std::string getKey()const{ return this->key; }

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
			//out << "\tKey = " << this->key << "\n";
			return out;
		}
};

class KeyStrFactory : public RegisterFactory{
	public:
		KeyStrFactory(){}
		virtual ~KeyStrFactory(){}

		virtual RegisterFactory* duplicate()const{ return new KeyStrFactory(); }

		char* operator()(Register& reg,char* data){
			KeyStr& akey = dynamic_cast<KeyStr&>(reg);

			std::string keystr  = akey.getKey();

			strcpy(data,keystr.c_str());
			data+=akey.getSize();

			return data;
		}

		virtual Register* operator()(char* data){
			return new KeyStr(std::string(data));
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

class ValueNullFactory : public RegisterFactory{
	public:
		ValueNullFactory(){}
		~ValueNullFactory(){}

		RegisterFactory* duplicate()const{ return new ValueNullFactory(); }

		char* operator()(Register& reg,char* data){
			return data;
		}

		Register* operator()(char* data){
			return new ValueNull();
		}
};
#endif /* __FACTORY_H__ */
