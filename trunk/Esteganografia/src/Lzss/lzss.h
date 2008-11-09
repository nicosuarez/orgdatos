#ifndef __LZSS_H_
#define __LZSS_H_

#include <fstream.h>
#include <string.h>
#include <vector.h>



typedef union{
		    unsigned long vlong;
		    unsigned char st[4];
}Valor;
class Lzss{
	private:
		static const unsigned int sizeWin=16;
		static const unsigned int sizeBuffer=63;
		static const unsigned int lMax=9;
		static const unsigned int lMin=2;
		const unsigned int bitsLong;
		const int bitsPos;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> windows;

		/*Para comprimir*/
		void insertCodePosLong(unsigned int longMatch,unsigned int posMatch,
				std::ostream* fp,unsigned char* lastChar,unsigned int& emptyBits);
		void insertChar(char c, std::ostream* fp,unsigned char* lastChar,
						unsigned int& emptyBits);
		unsigned int getCantBitsPos();
		unsigned int getCantBitsLong();
		void save(std::ostream* fp,unsigned char& lastChar, unsigned int& emptyBits,
						 unsigned int valueToemptyBits=8,unsigned char c=0x00);

		/*guardo el tamaño del arch original en varLong*/
		void writeVarLong(std::ifstream* fp,std::ofstream* fpTarget);
		/*lee el ifstream la cantidad de caracteres indicada y los carga en windows*/
		void readFile(std::ifstream& fp,unsigned int cant);
		/*Fin de compresor*/

		/*descompresor*/
		char getChar (std::ifstream* origin,unsigned int& nBit,unsigned char& lastChar);

		//modifica nBit aumentandolo
		unsigned int getFlag(std::ifstream* fpOrigin,unsigned int& floor, unsigned char& lastChar);

		//carga el st con la descompresion de ese posLong
		unsigned int getPosLong (std::ifstream* fpOrigin,std::ofstream* fpTarget,
								unsigned int& nBit,unsigned char& lastChar);

		unsigned long readVarLong(std::ifstream* fp);
		/*Fin de descompresion*/
	public:
		Lzss();
		virtual ~Lzss();
		void compress(const char* toCompress,const char* temporaryFile);
		void uncompress(const char* origin, const char* target);

};

#endif //__LZSS_H_
