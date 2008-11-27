#ifndef __STORAGE_EXCPETION_H__
#define __STORAGE_EXCPETION_H__

#include <string>

class StorageException{
    protected:
        std::string message;

    public:
        StorageException(const std::string& amessage) : message(amessage) {
        }

        const char* what() const throw(){
            return message.c_str();
        }
};

#endif /* __STORAGE_EXCPETION_H__ */
