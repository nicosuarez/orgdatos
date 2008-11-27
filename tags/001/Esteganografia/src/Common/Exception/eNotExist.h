#ifndef ENOTEXIST_H_
#define ENOTEXIST_H_

#include <string>
#include <exception>

using std::exception;

class eNotExist: public exception{
    protected:
        std::string message;

    public:
        eNotExist(const std::string& amessage): exception(), message(amessage)
        {
        }
        
        ~eNotExist()throw()
        {
        }

        const char* what() const throw()
        {
            return message.c_str();
        }
};

#endif /*ENOTEXIST_H_*/
