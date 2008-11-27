#ifndef __TRANSPOSITION__H__
#define __TRANSPOSITION__H__

#include "encrypter.h"
#include <fstream.h>
#include <string.h>

class Transposition{//:public Encrypt{
	private:
		static const unsigned int N=3;
		static const unsigned int NMAX=5;
		unsigned int currN;
		unsigned int currNmax;
	public:
		Transposition();
		~Transposition();

		static void readVarLong(ifstream* fp,ofstream* fpTarget);

		static void decrypt(const char* fileOrigin,const char* fileTarget);
		static void encrypt(const char* fileOrigin,const char* fileTarget);
};

#endif /*__TRANSPOSITION__H__*/
