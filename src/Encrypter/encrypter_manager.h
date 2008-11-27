#ifndef ENCRYPTER_MANAGER_H_
#define ENCRYPTER_MANAGER_H_

class EncrypterManager{
	public:
		static void encrypt(const char* fileOrigin,const char* fileTarget);
		static void decrypt(const char* fileOrigin,const char* fileTarget);
};


#endif /* ENCRYPTER_MANAGER_H_ */
