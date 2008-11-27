#ifndef EEXIST_H_
#define EEXIST_H_

#include <string>
#include <exception>

using std::exception;

class eExist: public exception{
    protected:
        std::string message;

    public:
        eExist(const std::string& amessage): exception(), message(amessage)
        {
        }
        
        ~eExist()throw()
        {
        }

        const char* what() const throw()
        {
            return message.c_str();
        }
};

#endif /*EEXIST_H_*/
