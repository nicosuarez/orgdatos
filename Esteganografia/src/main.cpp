#include <iostream>
#include "Common/Console.h"


int main(int argc, char *argv[])
{
	try
	{
		Console::Run(argc,argv);
	}
	catch(char* error)
    {
		std::cout << error << std::endl;
    }
	return EXIT_SUCCESS;
}
