#ifndef __PASSWORDMANAGER_H_
#define __PASSWORDMANAGER_H_

#include <string>
#include "Message.h"
#include "Constant.h"

class PasswordManager {
public:
	/* Password modes. */
	static const short NEW=0;
	static const short CHANGE = 1;

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

	static void stringToMsg(string str,Message msg);

	/**
	 * Extrae el password de msg
	 */
	static Message Extract(const Message& msg,const Message& msgTarget=Message(PATH_TARGET_DESCOMPRESS_CM));

	/**
	 * Guarda el password comprimido y encriptado en msgTarget
	 */
	static void Hide(const Message& msg,const Message& msgTarget=Message(PATH_PASS_FILE));

	/**
	* Crea el archivo de password
	* Lanza ex de eFile
	*/
	static void CreatePass(const Message& msg,short mode);

	/**
	 * Graba en un archivo los string de vStr y  su Date
	 */
	static void writeIntruder(tVecStr vStr);

	/*devuelve un vector con todos los intrusos y luego elimina el archivo intrusos*/
	static tVecStr getIntruders();

	/**
	 * Setea el nuevo password
	 */
	static bool ChangePass(const std::string& oldPass,const std::string& newPass);

};

#endif /* __PASSWORDMANAGER_H_ */
