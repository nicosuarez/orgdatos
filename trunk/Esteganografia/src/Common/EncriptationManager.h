
#ifndef __ENCRIPTATIONMANAGER__H_
#define __ENCRIPTATIONMANAGER__H_

#include "Message.h"

/**
 * Clase que se encarga de encriptar y desencriptar el mensaje a ocultar.
 */
class EncriptationManager
{
public:
	EncriptationManager();
	~EncriptationManager();

	/**
	 * llena el mensaje msgTarget.
	 */
	static Message Decrypt(const Message& msg);
	/**
	 * llena el mensaje msgTarget
	 */
	static Message Encrypt(const Message& msg);
private:
	static const std::string targetEncrypt;
	static const std::string targetDecrypt;

};
#endif // __ENCRIPTATIONMANAGER__H_
