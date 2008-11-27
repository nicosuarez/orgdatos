#ifndef __CELL_H__
#define __CELL_H__

#include <list>
#include "../Common/register_factory.h"
#include "../Common/register.h"

class Cell{
	private:
		static const char USED = 0x01;
		static const char IS_DELETED = 0x02;
		static const char IS_CHAINED = 0x04;
		static const char IS_CHAIN_BEGIN = 0x08;
		static const char IS_CHAIN_END = 0x10;
	public:
		char flags;
		unsigned int size;
		char* data;
		unsigned int nextCell;
		unsigned int offset;

	public:
		Cell(unsigned int offset);
		~Cell();

		char* getData(){ return this->data; }
		void setData(char* data,unsigned int size);


		static unsigned int getHeaderSize(){ return (sizeof(char)+sizeof(unsigned int)*2); }
		unsigned int getDataSize()const{	return this->size; }
		unsigned int getOffset()const{ return this->offset; }
		void setOffset(unsigned int offset){ this->offset=offset; }
		void setNextCell(unsigned int offset){ this->nextCell=offset; }
		unsigned int getNextCell(){ return this->nextCell; }

		bool isFree()const{ return !(flags&USED); }
		bool isDeleted()const{ return flags&IS_DELETED; }
		bool isChained()const{ return flags&IS_CHAINED; }
		bool isChainBegin()const{ return flags&IS_CHAIN_BEGIN; }
		bool isChainEnd()const{ return flags&IS_CHAIN_END; }

		void setChained(bool state);
		void setChainBegin(bool state);
		void setChainEnd(bool state);
		void setDeleted(bool state);
		void clearFlags(){ this->flags = 0; }


		void readHeader(char* data);
		void writeHeader(char* data)const;

		char* toBytes(char* data)const;

		std::ostream& toOstream(std::ostream& out);

		void split(std::list<Cell*>& cells,unsigned int cellSize);
};

#endif /* __CELL_H__ */
