#ifndef __CONTROL_REGISTER_H__
#define __CONTROL_REGISTER_H__

#include "../Common/register.h"

class ControlRegister : public Register {
	public:
		static const char OVER_THRESHOLD = 0x01;
		static const char KEY_TYPE = 0x02;
		static const unsigned int NO_OFFSET = -1;
	private:

		unsigned int offset;
		char flags;
		Register* reg;
	public:
		ControlRegister(char flags){
			this->flags = flags;
			this->reg = NULL;
			this->offset = NO_OFFSET;
		}

		ControlRegister(){
			this->flags = 0;
			this->reg = NULL;
			this->offset = NO_OFFSET;
		}

		ControlRegister(const Register& reg,unsigned int threshold,char flags){
			this->reg = reg.duplicate();
			this->offset = NO_OFFSET;
			this->flags = flags;

			if(this->getSize()>=threshold)
				this->flags |= OVER_THRESHOLD;

		}

		ControlRegister(const ControlRegister& reg){
			this->reg = reg.reg->duplicate();
			this->flags = reg.flags;
			this->offset = reg.offset;
		}

		~ControlRegister(){
			delete this->reg;
		}

		void setRegister(Register* reg){ this->reg=reg;	}
		void setFlags(char flags){ this->flags = flags; }
		void setOffset(unsigned int offset){ this->offset = offset; }
		unsigned int getOffset()const{ return this->offset; }
		char getFlags()const{ return this->flags; }
		Register& getRegister()const{ return *this->reg; }

		Register* duplicate() const{ return new ControlRegister(*this); }

		void setFields(const Register& b2){
			this->reg->setFields(*dynamic_cast<const ControlRegister&>(b2).reg);
		}

		virtual unsigned int getSize()const{
			if(isOver())
				return sizeof(unsigned int)+1;
			return this->reg->getSize()+1;
		}

		virtual bool operator<(const Register& r2)const{
			return ( (*this->reg) < (*dynamic_cast<const ControlRegister&>(r2).reg) );
		}

		virtual std::ostream& toOstream(std::ostream& out)const{
			if(isOver())
				out << "\tOffset: " << this->offset;
			this->reg->toOstream(out);
			return out;
		}

		bool isKeyType()const{ return this->flags&KEY_TYPE; }
		bool isValueType()const{ return !(this->flags&KEY_TYPE); }
		bool isOver()const{ return this->flags&OVER_THRESHOLD; }
		void setOverOn(){ this->flags |= OVER_THRESHOLD; }
		void setOverOff(){ this->flags &= ~OVER_THRESHOLD; }

		static unsigned int getThreshold(const Register& r1,unsigned int nodeSize,unsigned int controlSize){
			if((nodeSize/2)<(r1.getSize() + controlSize))
				return 0;
			return (nodeSize/2 - r1.getSize() - controlSize);
		}
};

#endif  /*__CONTROL_REGISTER_H__ */
