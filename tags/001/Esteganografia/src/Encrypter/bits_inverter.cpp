#include "bits_inverter.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "../Common/Exception/eFile.h"

using namespace std;

//BitsInverter::BitsInverter(){}

void BitsInverter::encrypt(const char* fileOrigin,const char* fileTarget){
	ifstream fpOrigin(fileOrigin,ios::in|ios::binary);
	if (!fpOrigin.good())
		throw eFile("fallo archivo3");
	ofstream fpTarget(fileTarget,ios::out|ios::ate|ios::binary);
	if (!fpTarget.good())
		throw eFile("fallo archivo4");
	unsigned int currN=BitsInverter::BASE;
    while (!fpOrigin.eof()){
	    unsigned char c;
		fpOrigin.read((char*)&c,sizeof (char));
        if (!fpOrigin.eof()){
			c=~c;
			c-=currN;
			fpTarget.write((char*)&(c),sizeof(char));
			if (currN==BitsInverter::MAXBASE)
				currN=BitsInverter::BASE;
			currN++;
        }
	}
    fpTarget.close();
    fpOrigin.close();
}

void BitsInverter::decrypt(const char* fileOrigin,const char* fileTarget){
	ifstream fpOrigin(fileOrigin,ios::in|ios::binary);
	if (!fpOrigin.good())
		throw eFile("fallo archivo");
	ofstream fpTarget(fileTarget,ios::out|ios::ate|ios::binary);
	if (!fpTarget.good())
		throw eFile("fallo archivo");
	unsigned int currN=BitsInverter::BASE;
	while (!fpOrigin.eof()){
	    unsigned char c;
        fpOrigin.read((char*)&c,sizeof(char));
        if (!fpOrigin.eof()){
			c=~c;
			c-=currN;
			fpTarget.write((char*)&(c),sizeof(char));
			if (currN==BitsInverter::MAXBASE)
				currN=BitsInverter::BASE;
			currN++;
        }
    }
	fpTarget.close();
	fpOrigin.close();
}
