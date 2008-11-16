#ifndef __PASSWORDMANAGER_H_
#define __PASSWORDMANAGER_H_

#include <string>
#include "Message.h"

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
};

#endif /* __PASSWORDMANAGER_H_ */
