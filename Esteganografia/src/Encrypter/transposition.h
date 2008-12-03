#ifndef __TRANSPOSITION__H__
#define __TRANSPOSITION__H__

#include <fstream>
#include <string>

class Transposition{
	private:
		static const unsigned int N=3;
		static const unsigned int NMAX=5;
		unsigned int currN;
		unsigned int currNmax;
	public:
		Transposition();
		~Transposition();

		static void readVarLong(std::ifstream* fp,std::ofstream* fpTarget);

		static void decrypt(const char* fileOrigin,const char* fileTarget);
		static void encrypt(const char* fileOrigin,const char* fileTarget);
};

#endif /*__TRANSPOSITION__H__*/
