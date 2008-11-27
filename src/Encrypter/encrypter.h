#ifndef __ENCRYPTER__H__
#define __ENCRYPTER__H__

class Encrypter{

	public:
		Encrypter(){}
		virtual ~Encrypter(){}
		//devuelve lleno el encrypt con el mismo size
		static void encrypt(const char* fileOrigin,const char* fileTarget){};
		//devuelve lleno toUnencrypt con el mismo size
		static void decrypt(const char* fileOrigin,const char* fileTarget){};
};

#endif /*__ENCRYPTER__H__*/
