#ifndef __BPP_LEVEL_REGISTER_H
#define __BPP_LEVEL_REGISTER_H

#include "node_register.h"

class LevelRegister : public NodeRegister {
	private:
		unsigned int  rightChild;
	public:
		LevelRegister();
		LevelRegister(const Register& key ,unsigned int rightChild);
		LevelRegister(const LevelRegister& lr);
		virtual ~LevelRegister();

		virtual void setRightChild(unsigned int offset){ this->rightChild = offset; }
		virtual unsigned int getRightChild()const{ return rightChild; }

		virtual unsigned int getSize()const;
		virtual NodeRegister* duplicate()const;
		virtual char* toBytes(char* data,ControlRegisterFactory& factory)const;
		virtual char* toRegister(char* data,ControlRegisterFactory& factory);
		virtual std::ostream& toOstream(std::ostream& out)const;
};

#endif /* __BPP_LEVEL_REGISTER_H */
