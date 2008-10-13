#ifndef __LZSS_H_
#define __LZSS_H_

#include <string>
#include <vector>

class Lzss{
	private:
		static const unsigned int sizeWin=4;
		static const unsigned int sizeBuffer=4;
		static const unsigned int lMax=4;
		static const unsigned int lMin=0;
		const int bitsLong;
		const int bitsPos;
		std::vector<unsigned char> buffer;

		//Para comprimir
		void insertCodePosLong(unsigned int longMatch,unsigned int posMatch,std::vector<unsigned char>* ans,unsigned int& emptyBits);
		void insertChar(const char c,std::vector<unsigned char>* ans, unsigned int& emptyBits);
		unsigned int getCantBitsPos();
		unsigned int getCantBitsLong();
		//descompresor
		char getChar (const unsigned char* compress, unsigned int& nBit,unsigned int& floor);
		//modifica nBit aumentandolo
		unsigned int getFlag(const unsigned char* compress,unsigned int& floor, unsigned int& nBit);
		//carga el st con la descompresion de ese posLong
		void getPosLong (const unsigned char* compress,std::string& st, unsigned int& nBit,unsigned int& floor);

	public:
		Lzss();
		virtual ~Lzss();
		std::string compress(std::string toCompress);
		std::string uncompress(const unsigned char* compress, unsigned int cant);

};

#endif //__LZSS_H_
