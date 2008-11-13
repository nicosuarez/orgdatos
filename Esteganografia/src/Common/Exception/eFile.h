#ifndef EFILE_H_
#define EFILE_H_
#include <string>
class eFile{
    protected:
        std::string message;

    public:
        eFile(const std::string& amessage) : message(amessage) {
        }

        const char* what() const{
            return message.c_str();
        }
};

#endif /* EFILE_H_ */
