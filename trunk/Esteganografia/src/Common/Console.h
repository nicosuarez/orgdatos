#ifndef CONSOLE_H_
#define CONSOLE_H_

/**
 * Clase que se encarga de correr el hilo principal
 **/
class Console
{
public:
	static int Run(int argc,char* argv[]);
	static void ShowInitialMessage();
	static void ShowPrompt();
};

#endif /*CONSOLE_H_*/
