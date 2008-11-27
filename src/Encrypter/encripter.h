#ifndef __ENCRYPTER__H__
#define __ENCRYPTER__H__

class Encrypter{

	public:
		Encrypter(){}
		virtual ~Encrypter(){}
		//devuelve lleno el encrypt con el mismo size
		static void encrypt(unsigned char* st, unsigned int size)=0;
		//devuelve lleno toUnencrypt con el mismo size
		virtual void unencrypt(unsigned char* st, unsigned int size)=0;

};

#endif /*__ENCRYPTER__H__*/
