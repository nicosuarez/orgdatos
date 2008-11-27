#ifndef ENOTSPACE_H_
#define ENOTSPACE_H_

#include <string>
#include <exception>

using std::exception;

class eNotSpace: public exception{
    protected:
        std::string message;

    public:
    	eNotSpace(const std::string& amessage): exception(), message(amessage)
        {
        }
        
        ~eNotSpace()throw()
        {
        }

        const char* what() const throw()
        {
            return message.c_str();
        }
};

#endif /*ENOTSPACE_H_*/
