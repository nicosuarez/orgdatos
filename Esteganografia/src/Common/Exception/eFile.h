#ifndef EFILE_H_
#define EFILE_H_
#include <string>

class eFile
{
	std::string msg;
	public:
		eFile( std::string error){ this->msg = error;};  
		virtual const char* what() const throw()
		  {
			  return msg.c_str();
		  }

};

#endif /*EFILE_H_*/
