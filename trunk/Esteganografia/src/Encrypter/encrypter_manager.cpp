#include "encrypter_manager.h"
#include "bits_inverter.h"
#include "transposition.h"
#include "../Lzss/lzss.h"
#include <stdio.h>

using std::cout;

void EncrypterManager::encrypt(const char* fileOrigin,const char* fileTarget){
	std::string stTarget="./alaPipetua3.dat";
	Transposition::encrypt(fileOrigin,stTarget.c_str());
	BitsInverter::encrypt(stTarget.c_str(),fileTarget);
	  if( remove( stTarget.c_str() ) != 0 )
	    perror( "Error deleting file" );
}

void EncrypterManager::decrypt(const char* fileOrigin,const char* fileTarget){
	std::string stTarget="./alaPipetua.dat";
	BitsInverter::decrypt(fileOrigin,stTarget.c_str());
	Transposition::decrypt(stTarget.c_str(),fileTarget);
	if( remove( stTarget.c_str()) != 0 )
	    perror( "Error deleting file" );

}
