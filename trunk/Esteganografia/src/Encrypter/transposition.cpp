#include "transposition.h"
#include "../Common/Exception/eFile.h"
#include <string>
#include <iostream>
#include <iomanip>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;


Transposition::Transposition(){
	this->currN=Transposition::N;
	this->currNmax=Transposition::NMAX;
}

Transposition::~Transposition(){}

void Transposition::encrypt(const char* fileOrigin,const char* fileTarget){
    ifstream fpOrigin(fileOrigin,ios::in|ios::binary);
    if (!fpOrigin.good())
    	throw eFile("fallo archivo5");
    ofstream fpTarget(fileTarget,ios::out|ios::ate|ios::binary);
	if (!fpTarget.good())
		throw eFile("fallo archivo6");
	unsigned int currN=Transposition::N;
	readVarLong(&fpOrigin,&fpTarget);
	while(!fpOrigin.eof()){
        unsigned char* st=new unsigned char[currN];
		fpOrigin.read(reinterpret_cast<char*>(st),sizeof(char)*currN);
		unsigned int roof = fpOrigin.gcount();
		if (roof!=0){
			unsigned int subFloor=0;
			for(unsigned int distance=roof-1;
				distance>subFloor;distance--,subFloor++){
				unsigned char c=st[distance];
				st[distance]=st[subFloor];
				st[subFloor]=c;
			}
		}
		fpTarget.write((char*)st,sizeof(char)*roof);
		delete st;
		if (currN==Transposition::NMAX)
			currN=Transposition::N;
		else
			currN++;
	}
	fpTarget.close();
	fpOrigin.close();
}


void Transposition::readVarLong(ifstream* fp,ofstream* fpTarget) {
	unsigned char aux;
	unsigned char prox;
	bool last = false;
	while (last == false) {
		fp->read((char*)&aux,sizeof(char));
		if(fp->eof())
			return;
		prox = aux >> 7;
		if (prox == 0)
			last = true;
		fpTarget->write((char*)&aux,sizeof(char));
	}
}

void Transposition::decrypt(const char* fileOrigin,const char* fileTarget){
    ifstream fpOrigin(fileOrigin,ios::in|ios::binary);
	ofstream fpTarget(fileTarget,ios::out|ios::ate|ios::binary);
	if (!fpOrigin.good())
		throw eFile("fallo archivo");
	if (!fpTarget.good())
		throw eFile("fallo archivo");
	readVarLong(&fpOrigin,&fpTarget);
	unsigned int currN=Transposition::N;
	while (!fpOrigin.eof()){
		unsigned char* st=new unsigned char[currN];
		fpOrigin.read(reinterpret_cast<char*>(st),sizeof(char)*currN);
		unsigned int roof = fpOrigin.gcount();
		if (roof!=0){
			unsigned int subFloor=0;
			for(unsigned int distance=roof-1;distance>subFloor;distance--,subFloor++){
				unsigned char c=st[distance];
				st[distance]=st[subFloor];
				st[subFloor]=c;
			}
		}
		if (currN==Transposition::NMAX)
			currN=Transposition::N;
		else
			currN++;
		fpTarget.write((char*)st,sizeof(char)*roof);
		delete st;
	}
	fpTarget.close();
	fpOrigin.close();
}
