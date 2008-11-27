#ifndef EBROKENPROGRAM_H_
#define EBROKENPROGRAM_H_

#include <string>

class eBrokenProgram {
	protected:
		std::string message;
	public:
		eBrokenProgram(const std::string& amessage) : message(amessage){}
		virtual ~eBrokenProgram(){}
		const char* what() const{
			return message.c_str();
		}
};

#endif /* EBROKENPROGRAM_H_ */
