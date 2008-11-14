#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include "../bpptree.h"
#include "../register_pack.h"

using namespace bpptree;

class KeyKeyVal : public Register{
	private:
		unsigned int key;
	public:
		KeyKeyVal(unsigned int key){
			this->key = key;
		}
		KeyKeyVal(const KeyKeyVal& k2){
			this->key = k2.key;
		}
		
		unsigned int getKey()const{ return this->key;  }

		Register* duplicate()const{
			return (new KeyKeyVal(*this));
		}

		void setFields(const Register& b2){
			const KeyKeyVal& temp = dynamic_cast<const KeyKeyVal&>(b2);
			this->key = temp.key;
		}

		unsigned int getSize()const {
			return (sizeof(unsigned int));
		};

		bool operator<(const Register& b2)const{
			const KeyKeyVal& temp = dynamic_cast<const KeyKeyVal&>(b2);
			return (this->key<temp.key);
		}

		std::ostream& toOstream(std::ostream& out)const{
			out << this->key;
			return out;
		}
};


class KeyVal : public Register{
	private:
		std::string key;
		unsigned int value;
	public:
		KeyVal(const std::string& key,unsigned int value){
			this->key   = key;
			this->value = value;
		}
		KeyVal(const KeyVal& k2){
			this->key   = k2.getKey();
			this->value = k2.getValue();
		}

		std::string getKey()const{ return this->key;  }
		unsigned int getValue()const{ return this->value; }

		Register* duplicate()const{
			return (new KeyVal(*this));
		}

		void setFields(const Register& b2){
			const KeyVal& temp = dynamic_cast<const KeyVal&>(b2);
			this->key = temp.getKey();
			this->value = temp.getValue();
		}

		unsigned int getSize()const {
			return (sizeof(unsigned int)+sizeof(char)*20);
		};

		bool operator<(const Register& b2)const{
			const KeyVal& temp = dynamic_cast<const KeyVal&>(b2);
			return (this->value<temp.getValue());
		}

		Register* getKeyRegister()const{
			KeyKeyVal* reg = new KeyKeyVal(this->value);
			return reg;
		}

		std::ostream& toOstream(std::ostream& out)const{
			out << "\t\t Key   : " << this->key << std::endl;
			out << "\t\t Value : " << this->value << std::endl;
			return out;
		}
};


class KeyKeyValFactory : public RegisterFactory{
	public:
		KeyKeyValFactory(){}
		~KeyKeyValFactory(){}

		RegisterFactory* duplicate()const{ return new KeyKeyValFactory(); }

		Register* operator ()(char* data)const{
			char* temp = data;
			unsigned int tempVal;
			memcpy(&tempVal,temp,sizeof(unsigned int));
			return (new KeyKeyVal(tempVal));
		}
		
		char* operator ()(const Register& reg,char* data)const{
			const KeyKeyVal& kkvreg = dynamic_cast<const KeyKeyVal&>(reg);
			char* temp = data;
			unsigned int tempValue = kkvreg.getKey();
			memcpy(temp,&tempValue,sizeof(unsigned int));
			temp+=sizeof(unsigned int);
			return temp;
		}
};

class KeyValFactory : public RegisterFactory{
	public:
		KeyValFactory(){}
		~KeyValFactory(){}

		RegisterFactory* duplicate()const{ return new KeyValFactory(); }

		Register* operator ()(char* data)const{
			char* temp = data;
			char keyTemp[20];
			unsigned int tempVal;
			memset(keyTemp,0,sizeof(char)*20);
			memcpy(keyTemp,temp,sizeof(char)*20);
			temp += sizeof(char)*20;
			memcpy(&tempVal,temp,sizeof(unsigned int));
			return (new KeyVal(std::string(keyTemp),tempVal));
		}
		
		char* operator ()(const Register& reg,char* data)const{
			const KeyVal& kvreg = dynamic_cast<const KeyVal&>(reg);
			char* temp = data;
			char tempKey[20];
			unsigned int tempValue = kvreg.getValue();
			memset(tempKey,0,sizeof(char)*20);
			memcpy(tempKey,kvreg.getKey().c_str(),kvreg.getKey().length());
			memcpy(temp,tempKey,sizeof(char)*20);
			temp+=sizeof(char)*20;
			memcpy(temp,&tempValue,sizeof(unsigned int));
			temp+=sizeof(unsigned int);
			return temp;
		}
};

int main(int argc,char** argv){
	KeyValFactory kvf;
	KeyKeyValFactory kkvf;	
	BppTree* bpptree = new BppTree(128,kvf,kkvf,"./data/bpptree.dat");
	
	unsigned int keys = 60;
	for(unsigned int c=0;c<keys;c++){
		unsigned int key = c;
		KeyVal kv("clave",key);
		bpptree->insert(kv);
	}
	
	std::cout << *bpptree;
	
	delete bpptree;

/*
	btree = new BTree(128,new KeyValFactory(),"./data/btree.dat");	
	for(unsigned int c=0;c<keys;c++){
		temp += itos(c);
		temp += ".dump";
	
		unsigned int key = keysArray[rand()%keys];
		kins2 >> key;
		//krmv >> key;
		KeyVal kv("clave",key);
		//if(key!=45)
			btree->remove(kv);
		//else
			//btree->remove(kv);
		//step << "Key " << key << " has been erased" << std::endl << std::endl << *btree;
		kdmprmv << key << std::endl;
	}
	rmv << *btree;

	delete btree;
	delete[] keysArray;

	btree = new BTree(128,new KeyValFactory(),"./data/btree.dat");	
	kins2.clear();
	kins2.seekg( 0 , std::fstream::beg );
	for(unsigned int c=0;c<keys;c++){
		unsigned int key = c;
		kins2 >> key;
		KeyVal kv("clave",key);
		btree->insert(kv);
	}
	
	delete btree;*/
	return 0;
}

std::string itos(int n){
	std::ostringstream temp;
	temp << n;
	return temp.str();
}
