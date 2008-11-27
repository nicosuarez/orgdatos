#ifndef __BITS_INVERTER__H__
#define __BITS_INVERTER__H__

#include "encrypter.h"

class BitsInverter:public Encrypter{
	private:
		unsigned int currN;
		static const unsigned int BASE=0;
		static const unsigned int MAXBASE=9;
	public:
		BitsInverter();
		~BitsInverter();
		static void encrypt(const char* fileOrigin,const char* fileTarget);
		static void decrypt(const char* fileOrigin,const char* fileTarget);
};

#endif /*__BITS_INVERTER__H__*/
