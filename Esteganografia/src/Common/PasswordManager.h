#ifndef __PASSWORDMANAGER_H_
#define __PASSWORDMANAGER_H_

#include <string>
#include "Message.h"
#include "Constant.h"

class PasswordManager {
public:
	PasswordManager();
	virtual ~PasswordManager();
	/**
	 * Devuelve true si el archivo de password existe.
	 * si el password esta corrupt lanza exception eBrokenProgram
	 */
	static bool ValidatePassword();
	/**
	 * Devuelve true si el password es el correcto
	 */
	static bool IsCorrectPass(const std::string& st);

	static void InsertNewPassword(string str,Message msg);

	/**
	 * Extrae el password de msg
	 */
	static Message Extract(Message msg,Message msgTarget=Message(PATH_TARGET_DESCOMPRESS_CM));

	/**
	 * Guarda el password comprimido y encriptado en msgTarget
	 */
	static void Hide(Message msg,Message msgTarget);

	/**
	* Crea el archivo de password
	* Lanza ex de eFile
	*/
	static void CreatePass(const Message& msg);

};

#endif /* __PASSWORDMANAGER_H_ */
