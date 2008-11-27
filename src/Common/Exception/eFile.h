#ifndef EFILE_H_
#define EFILE_H_
#include <string>
#include <exception>

using std::exception;

class eFile: public exception{
    protected:
        std::string message;

    public:
        eFile(const std::string& amessage): exception(), message(amessage)
        {
        }
        
        ~eFile()throw()
        {
        }

        const char* what() const throw()
        {
            return message.c_str();
        }
};

#endif /* EFILE_H_ */
